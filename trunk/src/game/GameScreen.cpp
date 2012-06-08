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

#include <SFML/Graphics.hpp>
#include "GameScreen.hpp"
#include "QsLog.h"

GameScreen::GameScreen() : mMouse(0, 0)
{
}

void GameScreen::render(sf::RenderTarget &target, sf::RenderStates states)
{
    if (mLevelPtr.isNull())
        return;
    mLevelPtr->draw(target, states);
    mMouse.draw(target, states);
}

void GameScreen::update(const sf::Time &dt)
{

}

void GameScreen::handleEvent(const sf::Event &event)
{
    // Move the mouse, but only inside the level
    const sf::Vector2i moveOffset = mMouse.handleEvent(event);
    if (moveOffset.x == 0 && moveOffset.y == 0)
        return;
    const sf::Vector2i newPos(mMouse.x() + moveOffset.x, mMouse.y() + moveOffset.y);
    if (isInLevel(newPos.x, newPos.y))
        mMouse.move(moveOffset.x, moveOffset.y);
}

bool GameScreen::start(TiledMapPtr level)
{
    if (!Screen::start(level))
        return false;

    QLOG_INFO() << "Game Screen : playing level" << level->info().filePath << ".";
    mMouse.loadTexture();

    const LevelInfo &info = mLevelPtr->info();
    levelSizeX = mLevelPtr->sizeX(), levelSizeY = mLevelPtr->sizeY();

    // Place the mouse
    // TODO : CHECK IF TILE VALID (== ground)
    unsigned int mouseX = 0, mouseY = 0;
    if (!info.mouseRandomPos && isInLevel(info.mousePosX, info.mousePosY))
        mouseX = info.mousePosX, mouseY = info.mousePosY;
    else // random pos
        mouseX = qrand() % levelSizeX, mouseY = qrand() % levelSizeY;
    mMouse.setX(mouseX).setY(mouseY);

    QLOG_INFO() << "Game Screen : starting game.";

    return true;
}

bool GameScreen::isInLevel(int x, int y) const
{
    return (x >= 0 && x < static_cast<int>(levelSizeX) &&
            y >= 0 && y < static_cast<int>(levelSizeY));
}
