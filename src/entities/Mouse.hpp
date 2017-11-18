#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "TiledEntity.hpp"

namespace sf
{
    class Event;
}
class TiledMap;

/** Mouse controlled by the player.
*
*/
class Mouse : public TiledEntity
{
public:
    /** Default constructor.
    */
    Mouse(int x, int y);

    /** Compute movement order from event.
    *@see move()
    *@return Movement order, in tiles units.
    */
    sf::Vector2i handleEvent(const sf::Event &event);

    /** Move the mouse, taking into account its environment.
    *@see handleEvent()
    *@param dx X move, in tiles units.
    *@param dy Y move, in tiles units.
    *@param level Reference to the current level.
    */
    void move(int dx, int dy, TiledMap &level);
};

#endif // MOUSE_HPP
