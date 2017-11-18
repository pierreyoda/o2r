#include <QStringList>
#include <SFML/Graphics/RenderTarget.hpp>
#include "TiledMap.hpp"
#include "QsLog.h"

using namespace sf;

const unsigned int TiledMap::SIZE_MIN_LIMIT_X = 5;
const unsigned int TiledMap::SIZE_MAX_LIMIT_X = 250;
const unsigned int TiledMap::SIZE_MIN_LIMIT_Y = 5;
const unsigned int TiledMap::SIZE_MAX_LIMIT_Y = 250;

const unsigned int &TILE_SIZE = TiledEntity::TILE_SIZE;

const QChar NULL_TILE_CHAR = QChar();
const TileInfo NULL_TILE_INFO = TileInfo();

TiledMap::TiledMap(unsigned int sizeX, unsigned int sizeY, const LevelInfo &info) :
    mSizeX(sizeX), mSizeY(sizeY), mInfo(info), mPathfinder(*this)
{
    // Fill the map with default tiles
    for (unsigned int i = 0; i < sizeY; i++)
    {
        mTiles.append(QList<Tile>());
        for (unsigned int j = 0; j < sizeX; j++)
            mTiles[i].append(Tile(j, i, '0'));
    }
}

TiledMap::~TiledMap()
{

}

bool TiledMap::buildMap()
{
    // (Re)load all textures
    mTilesVertices.clear();
    for (int i = 0; i < mTiles.size(); i++)
    {
        QList<Tile> &list = mTiles[i];
        for (int j = 0; j < list.size(); j++)
        {
            Tile &tile = list[j];
            const QChar &c = tile.getChar();
            if (!tile.loadTexture(true))
            {
                QLOG_ERROR() << QString("Cannot build tile from character '%1'")
                              .arg(c).toLocal8Bit().constData();
                return false;
            }
            // init the associated VertexArray if needed
            if (!mTilesVertices.contains(c))
                mTilesVertices.insert(c, TileGroupVertices(tile.getTexture()));
            TileGroupVertices &group = mTilesVertices[c];
            // add the 4 vertices of the VertexArray
            group.vertices.append(Vertex(Vector2f((j+0) * TILE_SIZE, (i+0) * TILE_SIZE),
                                                   Vector2f(0, 0)));
            group.vertices.append(Vertex(Vector2f((j+0) * TILE_SIZE, (i+1) * TILE_SIZE),
                                                   Vector2f(0, TILE_SIZE)));
            group.vertices.append(Vertex(Vector2f((j+1) * TILE_SIZE, (i+1) * TILE_SIZE),
                                                   Vector2f(TILE_SIZE, TILE_SIZE)));
            group.vertices.append(Vertex(Vector2f((j+1) * TILE_SIZE, (i+0) * TILE_SIZE),
                                                   Vector2f(TILE_SIZE, 0)));
        }
    }
    return true;
}

const QChar &TiledMap::getTileChar(unsigned int x, unsigned int y) const
{
    const Tile *tile = findTile(x, y);
    return (tile != 0 ? tile->getChar() : NULL_TILE_CHAR);
}

const TileInfo &TiledMap::getTileInfo(unsigned int x, unsigned int y) const
{
    const Tile *tile = findTile(x, y);
    return (tile != 0 ? tile->getInfo() : NULL_TILE_INFO);
}

TilePosList TiledMap::getTilesOfChars(const QList<QChar> &charFilters)
{
    TilePosList tiles;
    if (charFilters.empty())
        return tiles;
    for (int i = 0; i < mTiles.size(); i++)
    {
        QList<Tile> &list = mTiles[i];
        for (int j = 0; j < list.size(); j++)
            if (charFilters.contains(list[j].getChar()))
                tiles.append(sf::Vector2i(j, i));
    }
    return tiles;
}

TilePosList TiledMap::getTilesOfTypes(const QStringList &typeFilters)
{
    TilePosList tiles;
    if (typeFilters.empty())
        return tiles;
    for (int i = 0; i < mTiles.size(); i++)
    {
        QList<Tile> &list = mTiles[i];
        for (int j = 0; j < list.size(); j++)
            if (typeFilters.contains(list[j].getInfo().type))
                tiles.append(sf::Vector2i(j, i));
    }
    return tiles;
}

void TiledMap::setTileChar(unsigned int x, unsigned int y, const QChar &c,
                           bool allowOutsideIfContiguous, bool rebuildNow)
{
    // If outside and not contiguous, ignore
    if (!isInsideMap(x, y, true))
        return;
    // If outside but contiguous (tile on the left), add a tile if requested
    if (!isInsideMap(x, y, false))
    {
        if (allowOutsideIfContiguous && isInsideMap(x-1, y, false))
            mTiles[y].append(Tile(x, y, c));
        else
            return;
    }
    // If inside, change the tile char
    else
    {
        Tile &tile = mTiles[y][x];
        tile.setChar(c);
    }
    if (rebuildNow)
        buildMap();
    mPathfinder.reset();
}

void TiledMap::draw(RenderTarget &target, RenderStates states) const
{
    //BASIC DRAWING : slow
    // uses a default Vertex array transformed for each tile with X and Y positions
    /*for (unsigned int i = 0; i < mSizeY; i++)
        for (unsigned int j = 0; j < mSizeX; j++)
            mTiles[i][j].draw(target, states);*/

    // OPTIMIZED DRAWING : much more faster but needs more memory
    // groups all tiles of same type (and thus same texture) in a single VertexArray
    QHashIterator<QChar, TileGroupVertices> iter(mTilesVertices);
    while (iter.hasNext())
    {
        states.texture = iter.next().value().commonTexture.data(); // set texture for this type
        target.draw(iter.value().vertices, states); // draw all tiles of this type
    }
}

TilePosList TiledMap::computePath(const Vector2i &start, const Vector2i &end)
{
    TilePosList path;
    /*if (start == end || !isInsideMap(start.x, start.y)
            || !isInsideMap(end.x, end.y))
        return path; // no need to go further*/
    std::vector<void*> rawPath;
    // Compute path
    const int result = mPathfinder.computePath(start, end, rawPath);
    if (result != micropather::MicroPather::SOLVED)
        return path; // if unsolved : return empty path
    // Convert to TilePosList
    for (unsigned int i = 0; i < rawPath.size(); i++)
        path.append(mPathfinder.stateToPos(rawPath[i]));
    return path;
}

bool TiledMap::isInsideMap(unsigned int x, unsigned int y,
                           bool acceptUndefinedTiles) const
{
    const bool inMap = (x >= 0 && x < mSizeX && y >= 0 && y < mSizeY);
    if (!inMap)
        return false;
    return acceptUndefinedTiles? inMap : (static_cast<int>(x) < mTiles[y].size());
}

void TiledMap::resizeX(unsigned int sizeX)
{
    if (sizeX < SIZE_MIN_LIMIT_X || sizeX > SIZE_MAX_LIMIT_X || sizeX == mSizeX)
        return;
    if (sizeX > mSizeX)
        for (int i = 0; i < mTiles.size(); i++)
        {
            QList<Tile> &line = mTiles[i];
            for (unsigned int j = line.size(); j < sizeX; j++)
                line.append(Tile(j, i, '0'));
        }
    else
        for (int i = 0; i < mTiles.size(); i++)
        {
            QList<Tile> &line = mTiles[i];
            while (line.size() > sizeX && !line.isEmpty())
                line.removeLast();
        }
    mSizeX = sizeX;
}

void TiledMap::resizeY(unsigned int sizeY)
{
    if (sizeY < SIZE_MIN_LIMIT_Y || sizeY > SIZE_MAX_LIMIT_Y || sizeY == mSizeY)
        return;
    if (sizeY > mSizeY)
        for (unsigned int i = mTiles.size(); i < sizeY; i++)
        {
            mTiles.append(QList<Tile>());
            for (unsigned int j = 0; j < mSizeX; j++)
                mTiles[i].append(Tile(j, i, '0'));
        }
    else
        while (mTiles.size() > sizeY && !mTiles.isEmpty())
            mTiles.removeLast();
    mSizeY = sizeY;
}

const Tile *TiledMap::findTile(unsigned int x, unsigned int y) const
{
    return (isInsideMap(x, y, false) ? &mTiles[y][x] : 0);
}
