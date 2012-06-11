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
const unsigned int GameCanvas::DEFAULT_HEIGHT = TiledEntity::TILE_SIZE * 32;

const sf::Color DEFAULT_CLEAR_COLOR(0, 0, 0);

GameCanvas::GameCanvas(QWidget *parent, const QPoint &position) :
    QSfmlCanvas(parent, position, QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)),
    mRunning(false), mDefaultScreen(0), mCurrentScreen(0)
{
    setFixedSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    // Initialize FilespathProvider
    FilespathProvider::setModsLocation("mods/");
    FilespathProvider::setMainModFolder("original");
    QStringList nameFilters;
    nameFilters << "*.bmp" << "*.dds" << "*.jpg" << "*.png" << "*.tga" << "*.psd";
    FilespathProvider::setAssetsNameFilters(nameFilters);
    FilespathProvider::addMods(QStringList() << "zelda", true);
    FilespathProvider::refreshAssetsList();

    // Set up default tiles
    TilesTypesManager::setType('0', "void.png", TileInfo::TYPE_GROUND);
    TilesTypesManager::setType('1', "block.png", TileInfo::TYPE_BLOCK);
    TilesTypesManager::setType('2', "wall.png", TileInfo::TYPE_WALL);
}

GameCanvas::~GameCanvas()
{
    mLevelPtr.clear();
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
    mLevelPtr.clear();
    mLevelPtr = TiledMapPtr(TiledMapFactory::loadLevel(path));
    if (mLevelPtr.isNull() || !mLevelPtr->buildMap() ||
            (mLevelPtr->sizeX() == 0 && mLevelPtr->sizeY() == 0))
    {
        QLOG_ERROR() << "Game : cannot load level" << path << ".";
        mLevelPtr.clear();
        return false;
    }
    QLOG_INFO() << "Game : loaded level" << path << ".";

    // Resize the canvas
    const int w = mLevelPtr->sizeX() * TiledEntity::TILE_SIZE,
            h = mLevelPtr->sizeY() * TiledEntity::TILE_SIZE;
    setSize(sf::Vector2u(w, h));
    // Resize the window
    emit requestResize(w, h);
    // Resize the view
    mView.reset(sf::FloatRect(0, 0, w, h));
    setView(mView);

    return true;
}

void GameCanvas::setScreen(ScreenPtr screen, bool run)
{
    if (screen.isNull())
        return;
    mCurrentScreen = screen;
    mRunning = run;
}

void GameCanvas::onInit()
{
    QLOG_INFO() << "Initializing game.";
    mDefaultScreen = ScreenPtr(new EmptyScreen());
    mCurrentScreen = ScreenPtr(mDefaultScreen);
    mView.reset(sf::FloatRect(0, 0, width(), height()));
    setView(mView);
    mRunning = true;
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
    // Render current Screen
    mCurrentScreen->render(static_cast<sf::RenderWindow&>(*this));
}
