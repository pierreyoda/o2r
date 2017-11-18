#ifndef TILE_HPP
#define TILE_HPP

#include "TiledEntity.hpp"
#include "../managers/TilesTypesManager.hpp"

class TiledMap;

/** A Tile is a fragment of a TiledMap.
*
*/
class Tile : public TiledEntity
{
public:
    /** Default constructor.
    *@param x X position, in tiles units.
    *@param y Y position, in tiles units.
    *@param c Tile's character, unicode 16 bits
    *@param buildNow Load the tile's infos and texture now. True by default.
    *If set to false, loadTexture() must be called manually.
    */
    Tile(int x, int y, const QChar &c, bool buildNow = true);

    /** Update if needed and (re)load the texture.
    *Must be called at least once, AFTER having set the main mod and the tiles types.
    *@param updateInfo Update the TileInfo, false by default.
    *@see TiledEntity::loadTexture()
    *@see AssetsManager::getTexture() setChar()
    *@return True if successful, false otherwise.
    */
    bool loadTexture(bool updateInfo = false);

    /** Get the tile's informations.
    *@see TileInfo
    *@return The til's informations.
    */
    const TileInfo &getInfo() const { return mInfo; }

    /** Get the tile's character ID.
    *@see setChar()
    *@return The tile's character ID, unicode 16 bits.
    */
    const QChar &getChar() const { return mC; }

    /** Change the tile character ID and refresh the TileInfo.
    *@param c New tile character (ex. : '5'), unicode 16 bits.
    *@param updateTexture Update the texture? True by default.
    *@see loadTexture() getChar() TilesTypesManager::tileInfoFromChar()
    **@return True if TileInfo valid, false otherwise.
    */
    bool setChar(const QChar &c, bool updateTexture = true);

private:
    TileInfo mInfo;
    QChar mC;
};

#endif // TILE_HPP
