#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../map/TiledMap.hpp"

namespace sf
{
    class RenderTarget;
    class Event;
}

/** Abstract base class for all game screens.
*
*/
class Screen
{
public:
    /** Default constructor.
    *@param window Containing SFML window (needed for relative mouse position).
    */
    Screen(const sf::Window &window);
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
    *Default implementation : get level with null-check.
    *@param level Loaded level.
    *@return True if successful, false otherwise.
    */
    virtual bool start(TiledMapPtr level) = 0;

    /** Stop the screen.
    *Default implementation : drop the level pointer.
    */
    virtual void stop();

    /** Reload all used textures.
    *Default implementation : update the level.
    */
    virtual void reloadTextures();

protected:
    const sf::Window &mWindow;
    TiledMapPtr mLevelPtr;
    bool mStarted;
};

#endif // SCREEN_HPP
