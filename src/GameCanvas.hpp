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
#include "map/TiledMap.hpp"
#include "game/EmptyScreen.hpp"

typedef QSharedPointer<Screen> ScreenPtr;

/** The Game canvas, where the whole game is rendered.
*Actual game stuff is made in the Screen's subclasses.
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

    /** Get the loaded level.
    *@return Pointer to the loaded level (may be null).
    */
    TiledMapPtr loadedLevel() { return mLevelPtr; }

    /** Load a level from the given file path.
    *Warning : won't affect the current screen.
    *@param path Path to the level file.
    *@return True if successful, false otherwise.
    */
    bool loadLevel(const QString &path);

    /** Set the current screen.
    *@param screen Pointer to the new screen. Ignored if null.
    *@param run Start updating the new screen. True by default.
    */
    void setScreen(ScreenPtr screen, bool run = true);

    static const unsigned int DEFAULT_WIDTH;
    static const unsigned int DEFAULT_HEIGHT;
    
private:
    void onInit();
    void onUpdate();

    bool mRunning;
    TiledMapPtr mLevelPtr;
    EmptyScreen mDefaultScreen;
    ScreenPtr mCurrentScreen;
    sf::Clock mFrameClock;
};

#endif // GAMECANVAS_HPP
