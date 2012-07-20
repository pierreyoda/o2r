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

#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"
#include "entities/Mouse.hpp"
#include "entities/Cat.hpp"

/** The game screen.
*On start, places the Mouse and all AI entites.
*/
class GameScreen : public Screen
{
public:
    GameScreen();

    void render(sf::RenderTarget &target,
                sf::RenderStates states = sf::RenderStates::Default);

    void update(const sf::Time &dt);

    void handleEvent(const sf::Event &event);

    bool start(TiledMapPtr level);

    void reloadTextures();

private:
    sf::Vector2i randomEmptyPos(const TilePosList &emptyTiles,
                                const TilePosList forbiddenPos = TilePosList());

    Mouse mMouse;
    Cat mTestCat;
    unsigned int levelSizeX, levelSizeY;
};

#endif // GAMESCREEN_HPP
