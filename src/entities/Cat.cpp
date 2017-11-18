#include "Cat.hpp"
#include "Mouse.hpp"
#include "QsLog.h"

const float MOVE_TIME    = 0.75f; // time between each move, in s
const float WAITING_TIME = 3.0f;  // time before cheese transformation when blocked

Cat::Cat(int x, int y) : TiledEntity(x, y, "cat.png"), mOldMousePos(-1, -1),
    mBlocked(false)
{

}

void Cat::update(TiledMapPtr level, const Mouse &mouse)
{
    if (level.isNull())
        return;
    bool trackUpdated = false;
    // Update tracking path if needed
    const sf::Vector2i mousePos(mouse.x(), mouse.y());
    if (mousePos != mOldMousePos || mTrackingPath.isEmpty())
    {
        const sf::Vector2i currentPos(mX, mY);
        mTrackingPath = level->computePath(currentPos, mousePos);
        mOldMousePos = mousePos;
        trackUpdated = true;
    }
    // Track clock : determines cat speed
    else if (mTrackingClock.getElapsedTime().asSeconds() >= MOVE_TIME)
        mTrackingClock.restart();
    else
        return;

    // If cannot reach mouse : wait
    if (mTrackingPath.isEmpty() && isBlocked(*level))
    {
        if (!mBlocked)
        {
            mBlocked = true;
            mWaitingClock.restart();
            setTextureAlias("cat_awaiting.png");
        }
        return;
    }
    // Otherwise, track the mouse
    if (mBlocked)
    {
        setTextureAlias("cat.png");
        mBlocked = false;
    }
    const sf::Vector2i nextPos(mTrackingPath.takeFirst());
    mX = nextPos.x, mY = nextPos.y;
}

bool Cat::isBlocked(const TiledMap &map)
{
    return true;
}
