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

#include "GameCanvas.hpp"
#include "managers/FilespathProvider.hpp"
#include "managers/TilesTypesManager.hpp"
#include "factories/TiledMapFactory.hpp"
#include "QsLog.h"

const unsigned int GameCanvas::DEFAULT_WIDTH  = TiledEntity::TILE_SIZE * 32;
const unsigned int GameCanvas::DEFAULT_HEIGHT = TiledEntity::TILE_SIZE * 32
        + HudRectangle::HEIGHT;

const sf::Color DEFAULT_CLEAR_COLOR(0, 0, 0);

GameCanvas::GameCanvas(QWidget *parent, const QPoint &position) :
    QSfmlCanvas(parent, position, QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)),
    mRunning(false), mDefaultScreen(0), mCurrentScreen(0)
{
    setFixedSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

GameCanvas::~GameCanvas()
{
    mCurrentLevel.clear();
    mCurrentScreen.clear();
    mDefaultScreen.clear();
}

void GameCanvas::onPause()
{
    mRunning = false;
}

void GameCanvas::onResume()
{
    mRunning = true;
}

void GameCanvas::onRetranslate()
{

}

bool GameCanvas::loadLevel(const QString &path)
{
    // Load the level
    QLOG_INFO() << "Game : loading level" << path << ".";
    TiledMapPtr newLevel(TiledMapFactory::loadLevel(path));
    if (newLevel.isNull() || !newLevel->buildMap() ||
            (newLevel->sizeX() < TiledMap::SIZE_MIN_LIMIT_X &&
             newLevel->sizeY() < TiledMap::SIZE_MIN_LIMIT_Y))
    {
        QLOG_ERROR() << "Game : cannot load level" << path << ".";
        newLevel.clear();
        return false;
    }
    QLOG_INFO() << "Game : loaded level" << path << ".";

    setLevel(newLevel);

    return true;
}

void GameCanvas::setLevel(TiledMapPtr level)
{
    if (level.isNull())
        return;
    mCurrentLevel = level;
    adjustSizeToLevel();
}

bool GameCanvas::setScreen(ScreenPtr screen, bool start)
{
    if (screen.isNull())
        return false;
    mCurrentScreen->stop();
    mCurrentScreen = screen;
    mRunning = start;
    return (start ? mCurrentScreen->start(mCurrentLevel) : true);
}

void GameCanvas::onInit()
{
    QLOG_INFO() << "Initializing game.";
    mDefaultScreen = ScreenPtr(new EmptyScreen());
    mCurrentScreen = ScreenPtr(mDefaultScreen);
    mView.reset(sf::FloatRect(0, 0, width(), height()));
    setView(mView);
    mHudRectangle.setWidth(DEFAULT_WIDTH);
    mHudTransform.translate(0, HudRectangle::HEIGHT);
    mRunning = true;

    // Set fixed main window size
    setSize(sf::Vector2u(DEFAULT_WIDTH, DEFAULT_HEIGHT));
    emit requestResize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

void GameCanvas::onUpdate()
{
    // Update current Screen (if running)
    if (mRunning)
    {
        sf::Event event;
        while (pollEvent(event))
            mCurrentScreen->handleEvent(event);
        mCurrentScreen->update(mFrameClock.restart());
    }

    // Clear previous render
    clear(DEFAULT_CLEAR_COLOR);
    // Draw HUD rectangle in default view
    //setView(getDefaultView());
    draw(mHudRectangle);
    // Render current Screen in game view, taking in account HUD height
    //setView(mView);
    mCurrentScreen->render(static_cast<sf::RenderWindow&>(*this), mHudTransform);
}

void GameCanvas::adjustSizeToLevel()
{
    if (mCurrentLevel.isNull())
        return;
    // Resize the canvas
    const int w = mCurrentLevel->sizeX() * TiledEntity::TILE_SIZE,
            h = mCurrentLevel->sizeY() * TiledEntity::TILE_SIZE + HudRectangle::HEIGHT;
    setSize(sf::Vector2u(w, h));
    // Resize the window
    emit requestResize(w, h);
    // Resize the view
    mView.reset(sf::FloatRect(0, 0, w, h));
    setView(mView);
    // Resize the HUD
    mHudRectangle.setWidth(w);
}
