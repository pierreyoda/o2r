#include <SFML/Graphics.hpp>
#include "Screen.hpp"

Screen::Screen(const sf::Window &window) : mWindow(window), mLevelPtr(0),
    mStarted(false)
{

}

Screen::~Screen()
{
    mLevelPtr.clear();
}

bool Screen::start(TiledMapPtr level)
{
    mLevelPtr = level;
    mStarted = !mLevelPtr.isNull();
    return mStarted;
}

void Screen::stop()
{
    mStarted = false;
    mLevelPtr.clear();
}

void Screen::reloadTextures()
{
    if (!mLevelPtr.isNull())
        mLevelPtr->buildMap();
}
