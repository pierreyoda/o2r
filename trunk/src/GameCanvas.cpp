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
#include "QsLog.h"

unsigned int GameCanvas::DEFAULT_WIDTH  = 500;
unsigned int GameCanvas::DEFAULT_HEIGHT = 500;

GameCanvas::GameCanvas(QWidget *parent, const QPoint &position) :
    QSfmlCanvas(parent, position, QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)),
    mRunning(false)
{
    setMinimumSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    FilespathProvider::setModsLocation("mods/");
    FilespathProvider::setMainModFolder("original");
}

GameCanvas::~GameCanvas()
{

}

void GameCanvas::onStart()
{
    mRunning = true;
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

void GameCanvas::onInit()
{

}

void GameCanvas::onUpdate()
{
    // Clear screen
    if (mRunning)
        clear(sf::Color::White);
    else
        clear(sf::Color::Black);

    // Update entities

    // Draw entities
}
