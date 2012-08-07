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
#include "../managers/FilespathProvider.hpp"
#include "QsLog.h"

const QChar EditorScreen::MOUSE_POS_CHAR = 'm';
const sf::Color MOUSE_POS_INDICATOR_COLOR(50, 50, 50, 200);

EditorScreen::EditorScreen(const sf::Window &window) : Screen(window),
    mPlaceableChar(), mPlaceableCharUpdated(false), mLastPlacedPos(-1, -1)
{
}

void EditorScreen::render(sf::RenderTarget &target, sf::RenderStates states)
{
    if (mLevelPtr.isNull())
        return;
    mLevelPtr->draw(target, states);
    if (!mLevelPtr->info().mouseRandomPos)
        target.draw(mMousePosIndicator, states);
}

void EditorScreen::update(const sf::Time &dt)
{
    if (mPlaceableChar.isNull() || mLevelPtr.isNull() ||
            !sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return;
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    if (mousePos.x < 0 || mousePos.y < 0)
        return;
    mousePos /= static_cast<int>(TiledEntity::TILE_SIZE);
    // Is a placing needed? (avoid useless computation)
    if (!mPlaceableCharUpdated && mLastPlacedPos == mousePos)
        return;
    // Is the mouse inside the map?
    if (!mLevelPtr->isInsideMap(mousePos.x, mousePos.y, true))
        return;
    // Place the mouse starting position...
    if (mPlaceableChar == MOUSE_POS_CHAR)
    {
        if (!mLevelPtr->isInsideMap(mousePos.x, mousePos.y, false))
            return;
        mLevelPtr->info().mouseRandomPos = false;
        mLevelPtr->info().mousePosX = mousePos.x, mLevelPtr->info().mousePosY = mousePos.y;
        relocateMousePosIndicator();
    }
    // or a tile, if different from the current one
    else if (mLevelPtr->getTileChar(mousePos.x, mousePos.y) != mPlaceableChar)
        mLevelPtr->setTileChar(mousePos.x, mousePos.y, mPlaceableChar, true, true);
    mLastPlacedPos = mousePos;
    mPlaceableCharUpdated = false;
}

void EditorScreen::handleEvent(const sf::Event &event)
{

}

bool EditorScreen::start(TiledMapPtr level)
{
    if (!Screen::start(level))
        return false;
    QLOG_INFO() << QString("EditorScreen : started editing level (name = \"%1\", filepath = \"%2\").")
                   .arg(level->info().name,
                        level->info().filePath).toLocal8Bit().constData();

    // Init the mouse start position indicator (but shown only if needed)
    TexturePtr texturePtr = AssetsManager::getTexture("mouse.png");
    if (texturePtr.isNull())
        return false;
    mMousePosIndicator.setTexture(*texturePtr);
    mMousePosIndicator.setColor(MOUSE_POS_INDICATOR_COLOR);
    relocateMousePosIndicator();

    return true;
}

void EditorScreen::setPlaceableChar(const QChar &c)
{
    if (c.isNull() || c == ' ' || c == mPlaceableChar)
        return;
    mPlaceableChar = c;
    mPlaceableCharUpdated = true;
}

void EditorScreen::relocateMousePosIndicator()
{
    if (mLevelPtr.isNull())
        return;
    sf::Vector2u mousePos(mLevelPtr->info().mousePosX, mLevelPtr->info().mousePosY);
    if (!mLevelPtr->isInsideMap(mousePos.x, mousePos.y))
        return;
    if (mLevelPtr->getTileInfo(mousePos.x, mousePos.y).type !=
            TileInfo::TYPE_GROUND)
        mLevelPtr->setTileChar(mousePos.x, mousePos.y, '0', true, true);
    mousePos *= TiledEntity::TILE_SIZE;
    mMousePosIndicator.setPosition(mousePos.x, mousePos.y);
}
