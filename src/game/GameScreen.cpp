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

#include <QStringList>
#include <SFML/Graphics.hpp>
#include "GameScreen.hpp"
#include "QsLog.h"

GameScreen::GameScreen(const sf::Window &window) : Screen(window),
    mMouse(0, 0), mTestCat(-1, -1)
{
}

void GameScreen::render(sf::RenderTarget &target, sf::RenderStates states)
{
    if (mLevelPtr.isNull())
        return;
    mLevelPtr->draw(target, states);
    mMouse.draw(target, states);
    mTestCat.draw(target, states);
}

void GameScreen::update(const sf::Time &dt)
{
    mTestCat.update(mLevelPtr, mMouse);
}

void GameScreen::handleEvent(const sf::Event &event)
{
    // Move the mouse, but only inside the level
    const sf::Vector2i moveOffset = mMouse.handleEvent(event);
    if (moveOffset.x == 0 && moveOffset.y == 0)
        return;
    const sf::Vector2i newPos(mMouse.x() + moveOffset.x, mMouse.y() + moveOffset.y);
    if (mLevelPtr->isInsideMap(newPos.x, newPos.y))
        mMouse.move(moveOffset.x, moveOffset.y, *mLevelPtr);
}

bool GameScreen::start(TiledMapPtr level)
{
    if (!Screen::start(level))
        return false;

    QLOG_INFO() << "Game Screen : playing level" << level->info().filePath << ".";
    mMouse.loadTexture();
    const LevelInfo &info = mLevelPtr->info();
    levelSizeX = mLevelPtr->sizeX(), levelSizeY = mLevelPtr->sizeY();

    const TilePosList groundTiles = mLevelPtr->getTilesOfTypes(
                QStringList() << "GROUND");

    // Place the mouse
    unsigned int mouseX = 0, mouseY = 0;
    if (!info.mouseRandomPos &&
            mLevelPtr->getTileChar(info.mousePosX, info.mousePosY) == '0')
        mouseX = info.mousePosX, mouseY = info.mousePosY;
    else
    {
        sf::Vector2i pos = randomEmptyPos(groundTiles);
        if (!mLevelPtr->isInsideMap(pos.x, pos.y, false))
        {
            QLOG_ERROR() << "GameScreen : CANNOT PLACE MOUSE";
            return false;
        }
        mouseX = pos.x, mouseY = pos.y;
    }
    mMouse.setX(mouseX).setY(mouseY);

    // Place the test cat
    mTestCat.loadTexture();
    sf::Vector2i pos = randomEmptyPos(groundTiles, TilePosList()
                                      << sf::Vector2i(mouseX, mouseY));
    mTestCat.setX(pos.x).setY(pos.y);

    QLOG_INFO() << "Game Screen : starting game.";

    return true;
}

sf::Vector2i GameScreen::randomEmptyPos(const TilePosList &emptyTiles,
                                        const TilePosList forbiddenPos)
{
    if (emptyTiles.isEmpty())
        return sf::Vector2i(-1, -1);
    const unsigned int index = qrand() % emptyTiles.size();
    const sf::Vector2i &pos = emptyTiles[index];
    if (forbiddenPos.contains(pos))
        return sf::Vector2i(-1, -1);
    return pos;
}

void GameScreen::reloadTextures()
{
    mMouse.loadTexture();
    mTestCat.loadTexture();
    Screen::reloadTextures();
}
