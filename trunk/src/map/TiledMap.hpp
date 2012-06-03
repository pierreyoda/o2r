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

#include <vector>
#include "../entities/Tile.hpp"

/** A TiledMap handles a variable number of tiles to form a 2D map.
*
* @see Tile
*/
class TiledMap : public sf::Drawable
{
public:
    TiledMap(unsigned int sizeX, unsigned int sizeY);
    virtual ~TiledMap();

    bool rebuildMap();

    /** Draw the TiledMap to the given sf::RenderTarget.
    *Implements the abstract function from sf::Drawable.
    *@param target Target where the TiledEntity is drawn.
    *@param states Current render states.
    */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const;

private:
    unsigned int mSizeX, mSizeY;
    std::vector< std::vector<Tile> > mTiles;
};

#endif // TILEDMAP_HPP
