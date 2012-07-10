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

#ifndef CAT_HPP
#define CAT_HPP

#include <SFML/System/Clock.hpp>
#include "TiledEntity.hpp"
#include "../map/TiledMap.hpp"

class Mouse;

/** The cat is the enemy in Open Rodent's Revenge.
*Using TiledMapPathfinder class, it tracks the mouse (the player) and tries to eat it.
*If the player manages to trap the cat, it will be transform in cheese.
*/
class Cat : public TiledEntity
{
public:
    Cat(int x, int y);

    /** Update the cat.
    *@param map Current map.
    *@param mouse Mouse to track.
    */
    void update(TiledMapPtr level, const Mouse &mouse);

private:
    bool isBlocked(const TiledMap &map);

    sf::Vector2i mOldMousePos;
    TilePosList  mTrackingPath;
    sf::Clock    mTrackingClock;
    sf::Clock    mWaitingClock;
    bool         mBlocked;
};

#endif // CAT_HPP
