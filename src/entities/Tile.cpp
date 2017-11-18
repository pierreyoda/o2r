#include "Tile.hpp"

Tile::Tile(int x, int y, const QChar &c, bool buildNow) :
    TiledEntity(x, y, "void.png"), mC(c)
{
    if (buildNow)
        setChar(c, true);
}

bool Tile::loadTexture(bool updateInfo)
{
    if (updateInfo)
        setChar(mC, false);
    if (!mInfo.isValid)
        return false;
    return setTextureAlias(mInfo.textureAlias);
}

bool Tile::setChar(const QChar &c, bool updateTexture)
{
    if (c.isNull() || c == ' ')
        return false;
    mC = c;
    mInfo = TilesTypesManager::tileInfoFromChar(mC);
    return (updateTexture ? loadTexture(false) : mInfo.isValid);
}
