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

#ifndef TILEDMAP_HPP
#define TILEDMAP_HPP

#include <QHash>
#include <QPair>
#include <SFML/Graphics/VertexArray.hpp>
#include "../entities/Tile.hpp"
#include "LevelInfo.hpp"

class TiledMapFactory;

/** Group of tiles with the same type (and thus the same texture).
*Used in TiledMap, it allows to reduce the number of OpenGL calls,
*in other words to improve performances (gain of 1200 fps / +200% on my computer).
*/
struct TileGroupVertices
{
    TileGroupVertices() : commonTexture(0), vertices(sf::Quads)
    { }
    TileGroupVertices(TexturePtr texture) : commonTexture(texture),
        vertices(sf::Quads)
    { }

    TexturePtr commonTexture;
    sf::VertexArray vertices;
};

/** A TiledMap handles a variable number of tiles to form a 2D map.
*
* @see Tile
*/
class TiledMap : public sf::Drawable
{
public:
    TiledMap(unsigned int sizeX, unsigned int sizeY);
    virtual ~TiledMap();

    /** Load all tiles and build vertices map.
    *Must be called when tiles change.
    */
    bool buildMap();

    /** Draw the TiledMap to the given sf::RenderTarget.
    *Implements the abstract function from sf::Drawable.
    *@param target Target where the TiledEntity is drawn.
    *@param states Current render states.
    */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const;

    /** Get the LevelInfo.
    *@return Const reference to the level infos.
    */
    const LevelInfo &info() const { return mInfo; }

    /** Get the X size.
    *@return Map X size, in tiles units.
    */
    unsigned int sizeX() const { return mSizeX; }

    /** Get the Y size.
    *@return Map Y size, in tiles units.
    */
    unsigned int sizeY() const { return mSizeY; }

    static const unsigned int SIZE_LIMIT_X;
    static const unsigned int SIZE_LIMIT_Y;

private:
    unsigned int mSizeX, mSizeY;
    QList< QList<Tile> > mTiles;
    QHash<QChar, TileGroupVertices> mTilesVertices;
    LevelInfo mInfo;

    friend class TiledMapFactory;
};

#endif // TILEDMAP_HPP
