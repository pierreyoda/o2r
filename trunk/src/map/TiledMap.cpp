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

#include "TiledMap.hpp"

using namespace std;

TiledMap::TiledMap(unsigned int sizeX, unsigned int sizeY) :
    mSizeX(sizeX), mSizeY(sizeY)
{
    // Fill the map with default tiles
    for (unsigned int i = 0; i < sizeY; i++)
    {
        mTiles.push_back(vector<Tile>());
        for (unsigned int j = 0; j < sizeX; j++)
        {
            mTiles[i].push_back(Tile(j, i, '1'));
        }
    }
}

TiledMap::~TiledMap()
{

}

bool TiledMap::rebuildMap()
{
    for (unsigned int i = 0; i < mSizeY; i++)
        for (unsigned int j = 0; j < mSizeX; j++)
            if (!mTiles[i][j].loadTexture())
                return false;
    return true;
}

void TiledMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mSizeY; i++)
        for (unsigned int j = 0; j < mSizeX; j++)
            mTiles[i][j].draw(target, states);
}
