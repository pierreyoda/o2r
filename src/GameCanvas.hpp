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
#include <SFML/Graphics/View.hpp>
#include "QSfmlCanvas.hpp"
#include "map/TiledMap.hpp"
#include "game/EmptyScreen.hpp"
#include "ui/HudRectangle.hpp"

typedef QSharedPointer<Screen> ScreenPtr;

/** The Game canvas, where the whole game is rendered.
*Actual game stuff is made in the Screen's subclasses.
*
*Important : FilespathProvider must be initialized before running any screen.
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

    /** Get the current level.
    *@return Pointer to the current level (may be null).
    *@see setLevel() loadLevel()
    */
    TiledMapPtr level() { return mCurrentLevel; }

    /** Load a level from the given file path and set it as the current level.
    *Warning : won't affect the current screen.
    *@param path Path to the level file.
    *@return True if successful, false otherwise.
    *@see level() setLevel()
    */
    bool loadLevel(const QString &path);

    /** Set the current level and resize the canvas.
    *Warning : won't affect the current screen.
    *@param level Pointer to the level. Ignored if null.
    *@see level() loadLevel()
    */
    void setLevel(TiledMapPtr level);

    /** Set the current screen.
    *@param screen Pointer to the new screen. Ignored if null.
    *@param start Start the new screen (with the current level). True by default.
    *@return True if successful, false otherwise.
    */
    bool setScreen(ScreenPtr screen, bool start = true);

    /** Reload all used textures.
    */
    void reloadTextures();

    static const unsigned int DEFAULT_WIDTH;
    static const unsigned int DEFAULT_HEIGHT;

signals:
    void requestResize(int w, int h);
    
private:
    void onInit();
    void onUpdate();

    void adjustSizeToLevel();

    bool mRunning;
    TiledMapPtr mCurrentLevel;
    ScreenPtr mDefaultScreen;
    ScreenPtr mCurrentScreen;
    sf::Clock mFrameClock;
    sf::View mView;
    HudRectangle mHudRectangle;
    sf::Transform mHudTransform;
};

#endif // GAMECANVAS_HPP
