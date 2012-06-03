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

#ifndef TILESTYPESMANAGER_HPP
#define TILESTYPESMANAGER_HPP

#include <QChar>
#include <QString>


/** @class TileInfo
*@brief A TileInfo contains the Tile's texture alias and type.
*@see Tile
*/
struct TileInfo
{
    TileInfo() : isValid(false)
    { }
    TileInfo(std::string _textureAlias, std::string _type) :
        textureAlias(_textureAlias), type(_type), isValid(true)
    { }

    std::string textureAlias;
    std::string type;
    bool isValid;
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
    void setType(const QChar &c, const std::string &textureAlias,
                 const std::string &type);
}


#endif // TILESTYPESMANAGER_HPP

