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

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../map/TiledMap.hpp"

namespace sf
{
    class RenderTarget;
    class Event;
}

typedef QSharedPointer<TiledMap> TiledMapPtr;

/** Abstract base class for all game screens.
*
*/
class Screen
{
public:
    /** Default constructor.
    */
    Screen();
    virtual ~Screen();

    /** Render to the given sf::RenderTarget.
    *Note : on each frame screen clean is made by GameCanvas.
    *@param target Target where the TiledEntity is drawn.
    *@param states Current render states.
    */
    virtual void render(sf::RenderTarget &target,
                        sf::RenderStates states = sf::RenderStates::Default) = 0;

    /** Update.
    *@param dt Elapsed time since last update.
    */
    virtual void update(const sf::Time &dt) = 0;

    /** Handle event.
    *@param event Event to handle.
    */
    virtual void handleEvent(const sf::Event &event) = 0;

    /** (Re)start the screen with the specified level.
    *@param level Loaded level.
    *@return True if successful, false otherwise.
    */
    virtual bool start(TiledMapPtr level);

protected:
    TiledMapPtr mLevelPtr;
    bool mStarted;
};

#endif // SCREEN_HPP
