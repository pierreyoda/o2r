#ifndef TILESTYPESMANAGER_HPP
#define TILESTYPESMANAGER_HPP

#include <QChar>
#include <QString>
#include <QMap>

/** @class TileInfo
*@brief A TileInfo contains the Tile's texture alias and type.
*@see Tile
*/
struct TileInfo
{
    TileInfo() : isValid(false)
    { }
    TileInfo(QString _textureAlias, QString _type) :
        textureAlias(_textureAlias), type(_type), isValid(true)
    { }

    QString textureAlias;
    QString type;
    bool isValid;

    static const QString TYPE_GROUND, TYPE_BLOCK, TYPE_WALL;
};


/** Set of fonctions managing the different types of tiles.
*Each tile type has a character (ex : "0"), a texture alias (ex : "void.png")
*and a type for collisions (ex : "GROUND").
*
*By default, the game uses :
*@li "0" = "void.png"  = "GROUND" (no interaction)
*@li "1" = "block.png" = "BLOCK"  (mouse can move them)
*@li "2" = "wall.png"  = "WALL"   (blocks mouse)
*
*This can be changed through LES (Level Extension System).
*
*@see Tile
*@see TiledMap
*/
namespace TilesTypesManager
{
    /** Get a tile info from its character.
    *@param c Tile's character (unicode 16 bits).
    *@return Associated tile info if existing, empty tile info otherwise.
    *@see setType()
    */
    TileInfo tileInfoFromChar(const QChar &c);

    /** Define a tile info from its character.
    *@param c Tile's character (unicode 16 bits).
    *@param textureAlias Tile's texture alias.
    *@param type Tile's type.
    *@see tileInfoFromChar()
    */
    void setType(const QChar &c, const QString &textureAlias,
                 const QString &type);

    /** Get the tiles types map as a const reference.
    *@return Tiles types map.
    */
    const QMap<QChar, TileInfo> &getMap();
}


#endif // TILESTYPESMANAGER_HPP

