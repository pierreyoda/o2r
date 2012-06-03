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
#include "QsLog.h"

const unsigned int GameCanvas::DEFAULT_WIDTH  = TiledEntity::TILE_SIZE * 32;
const unsigned int GameCanvas::DEFAULT_HEIGHT = TiledEntity::TILE_SIZE * 32;

const sf::Color DEFAULT_CLEAR_COLOR(128, 128, 0); // background color in "original" mod

GameCanvas::GameCanvas(QWidget *parent, const QPoint &position) :
    QSfmlCanvas(parent, position, QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)),
    mRunning(false), mMouse(0, 0)
{
    setMinimumSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    // Initialize FilespathProvider
    FilespathProvider::setModsLocation("mods/");
    FilespathProvider::setMainModFolder("original");
    QStringList nameFilters;
    nameFilters << "*.bmp" << "*.dds" << "*.jpg" << "*.png" << "*.tga" << "*.psd";
    FilespathProvider::setAssetsNameFilters(nameFilters);
    FilespathProvider::addMods(QStringList() << "zelda", true);
    FilespathProvider::refreshAssetsList();

    // Set up default tiles
    TilesTypesManager::setType('0', "void.png", "GROUND");
    TilesTypesManager::setType('1', "block.png", "BLOCK");
    TilesTypesManager::setType('2', "wall.png", "WALL");
}

GameCanvas::~GameCanvas()
{
    mLevelPtr.reset();
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
    mLevelPtr.reset(new TiledMap(32, 32));
    if (!mLevelPtr->rebuildMap())
    {
        QLOG_ERROR() << "Game : cannot load level" << path << ".";
        return false;
    }
    QLOG_INFO() << "Game : loaded level" << path << ".";
    return true;
}

void GameCanvas::onInit()
{
    QLOG_INFO() << "Initializing game.";
    mMouse.loadTexture();
    mMouse.setX(qrand() % 30).setY(qrand() % 30);
    loadLevel("levels/1.txt");
    QLOG_INFO() << "Starting game.";
    mRunning = true;
}

void GameCanvas::onUpdate()
{
    // Clear screen
    clear(DEFAULT_CLEAR_COLOR);

    // Update entities (if running)
    if (mRunning)
    {
        sf::Event event;
        while (pollEvent(event))
        {
            mMouse.handleEvent(event);
        }
    }

    // Draw map and entities
    if (!mLevelPtr.isNull())
        mLevelPtr->draw(static_cast<sf::RenderWindow&>(*this));
    mMouse.draw(static_cast<sf::RenderWindow&>(*this));
}
