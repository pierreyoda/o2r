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

#include <SFML/Window/Event.hpp>
#include "Mouse.hpp"
#include "../map/TiledMap.hpp"

Mouse::Mouse(int x, int y) : TiledEntity(x, y, "mouse.png")
{

}

sf::Vector2i Mouse::handleEvent(const sf::Event &event)
{
    if (event.type != sf::Event::KeyPressed)
        return sf::Vector2i();
    if (event.key.code == sf::Keyboard::Up)
        return sf::Vector2i(0, -1);
    else if (event.key.code == sf::Keyboard::Down)
        return sf::Vector2i(0, 1);
    else if (event.key.code == sf::Keyboard::Left)
        return sf::Vector2i(-1, 0);
    else if (event.key.code == sf::Keyboard::Right)
        return sf::Vector2i(1, 0);
    return sf::Vector2i();
}

void Mouse::move(int dx, int dy, TiledMap &level)
{
    const int newX = mX + dx, newY = mY + dy;
    const TileInfo &tileInfo = level.getTileInfo(newX, newY);
    // Ground tile : move
    if (tileInfo.type == TileInfo::TYPE_GROUND)
        mX = newX, mY = newY;
    // Block tile : move it if possible
    else if (tileInfo.type == TileInfo::TYPE_BLOCK)
    {
        int blockEndX = newX, blockEndY = newY;
        do {
            blockEndX += dx, blockEndY += dy;
        } while (level.getTileInfo(blockEndX, blockEndY).type == TileInfo::TYPE_BLOCK);
        if (level.getTileInfo(blockEndX, blockEndY).type != TileInfo::TYPE_GROUND)
            return;
        level.setTileChar(newX, newY, '0', false);
        level.setTileChar(blockEndX, blockEndY, '1', true);
        mX = newX, mY = newY;
    }
}
