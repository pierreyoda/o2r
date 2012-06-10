/*
    Open Rodent's Revenge is the open-source remake of Microsoft's game "Rodent's Revenge" (1991).
    Copyright (C) 2010-2012  Pierre-Yves Diallo (Pierreyoda).
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include <SFML/Graphics/RenderTarget.hpp>
#include "TiledMap.hpp"
#include "QsLog.h"

using namespace sf;

const unsigned int TiledMap::SIZE_LIMIT_X = 250;
const unsigned int TiledMap::SIZE_LIMIT_Y = 250;

const unsigned int &TILE_SIZE = TiledEntity::TILE_SIZE;

const QChar NULL_TILE_CHAR = QChar();

TiledMap::TiledMap(unsigned int sizeX, unsigned int sizeY) :
    mSizeX(sizeX), mSizeY(sizeY), mInfo()
{
    // Fill the map with default tiles
    for (unsigned int i = 0; i < sizeY; i++)
    {
        mTiles.append(QList<Tile>());
        for (unsigned int j = 0; j < sizeX; j++)
            mTiles[i].append(Tile(j, i, '1'));
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
            // keep in memory the index in the VertexArray
            tile.mVertexIndex = group.vertices.getVertexCount() / 4;
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

const QChar &TiledMap::getTileChar(unsigned int x, unsigned int y)
{
    if (!isInsideMap(x, y, false))
        return NULL_TILE_CHAR;
    return mTiles[y][x].getChar();
}

QList<sf::Vector2u> TiledMap::getTilesOfChars(const QList<QChar> &charFilters)
{
    QList<sf::Vector2u> tiles;
    if (charFilters.empty())
        return tiles;
    for (int i = 0; i < mTiles.size(); i++)
    {
        QList<Tile> &list = mTiles[i];
        for (int j = 0; j < list.size(); j++)
            if (charFilters.contains(list[j].getChar()))
                tiles.append(sf::Vector2u(j, i));
    }
    return tiles;
}

void TiledMap::setTileChar(unsigned int x, unsigned int y, const QChar &c,
                           bool optimizedRebuild)
{
    // TODO
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

bool TiledMap::isInsideMap(unsigned int x, unsigned int y,
                           bool acceptUndefinedTiles) const
{
    const bool inMap = (x >= 0 && x < mSizeX && y >= 0 && y < mSizeY);
    if (!inMap)
        return false;
    return acceptUndefinedTiles? inMap : (static_cast<int>(x) < mTiles[y].size());
}
