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

#ifndef GAMECANVAS_HPP
#define GAMECANVAS_HPP

#include <QScopedPointer>
#include "QSfmlCanvas.hpp"
#include "entities/Mouse.hpp"
#include "map/TiledMap.hpp"

/** The Game canvas, where all the game stuff (updating, drawing...) is actually made.
*
*/
class GameCanvas : public QSfmlCanvas
{
    Q_OBJECT
public:
    explicit GameCanvas(QWidget *parent, const QPoint &position);
    ~GameCanvas();

    void onPause();
    void onResume();
    void onRetranslate();

    bool loadLevel(const QString &path);

    static const unsigned int DEFAULT_WIDTH;
    static const unsigned int DEFAULT_HEIGHT;
    
private:
    void onInit();
    void onUpdate();

    bool mRunning;
    Mouse mMouse;
    QScopedPointer<TiledMap> mLevelPtr;
};

#endif // GAMECANVAS_HPP