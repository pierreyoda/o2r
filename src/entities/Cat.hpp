#ifndef CAT_HPP
#define CAT_HPP

#include <SFML/System/Clock.hpp>
#include "TiledEntity.hpp"
#include "../map/TiledMap.hpp"

class Mouse;

/** The cat is the enemy in Open Rodent's Revenge.
*Using TiledMapPathfinder class, it tracks the mouse (the player) and tries to eat it.
*If the player manages to trap the cat, it will be transform in cheese.
*/
class Cat : public TiledEntity
{
public:
    Cat(int x, int y);

    /** Update the cat.
    *@param map Current map.
    *@param mouse Mouse to track.
    */
    void update(TiledMapPtr level, const Mouse &mouse);

private:
    bool isBlocked(const TiledMap &map);

    sf::Vector2i mOldMousePos;
    TilePosList  mTrackingPath;
    sf::Clock    mTrackingClock;
    sf::Clock    mWaitingClock;
    bool         mBlocked;
};

#endif // CAT_HPP
