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
#include "EditorScreen.hpp"
#include "QsLog.h"

EditorScreen::EditorScreen() : mFirstClick(true), mClickText("Click again for pathfinding")
{
}

void EditorScreen::render(sf::RenderTarget &target, sf::RenderStates states)
{
    if (mLevelPtr.isNull())
        return;
    mLevelPtr->draw(target, states);
    if (!mFirstClick)
        target.draw(mClickText);
}

void EditorScreen::update(const sf::Time &dt)
{
}

void EditorScreen::handleEvent(const sf::Event &event)
{
    // A* test
    if (event.type == sf::Event::MouseButtonReleased)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2i mousePosTiles((int)mousePos.x / TiledEntity::TILE_SIZE,
                                   (int)mousePos.y / TiledEntity::TILE_SIZE);
        if (mFirstClick)
        {
            mFirstClickPos = mousePosTiles;
        }
        else
        {
            TilePosList path = mLevelPtr->computePath(mFirstClickPos, mousePosTiles);
            QLOG_INFO() << "PATH SIZE =" << path.size();
            QListIterator<sf::Vector2i> iter(path);
            while (iter.hasNext())
            {
                const sf::Vector2i pos = iter.next();
                mLevelPtr->setTileChar(pos.x, pos.y, '2', false);
            }
            mLevelPtr->buildMap();
        }
        mFirstClick = !mFirstClick;
    }
}

bool EditorScreen::start(TiledMapPtr level)
{
    if (!Screen::start(level))
        return false;
    QLOG_INFO() << QString("EditorScreen : started editing level (name = \"%1\").")
                   .arg(level->info().name).toLocal8Bit().constData();
    return true;
}
