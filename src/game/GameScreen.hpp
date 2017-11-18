#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"
#include "entities/Mouse.hpp"
#include "entities/Cat.hpp"
#include "entities/Trap.hpp"

/** The game screen.
*On start, places the Mouse and all AI entites.
*/
class GameScreen : public Screen
{
public:
    GameScreen(const sf::Window &window);

    void render(sf::RenderTarget &target,
                sf::RenderStates states = sf::RenderStates::Default);

    void update(const sf::Time &dt);

    void handleEvent(const sf::Event &event);

    bool start(TiledMapPtr level);

    void reloadTextures();

private:
    sf::Vector2i randomEmptyPos(const TilePosList &emptyTiles,
                                const TilePosList forbiddenPos = TilePosList(),
                                unsigned int attempts = 0);

    Mouse mMouse;
    QList<Cat> mCats;
    QList<Trap> mTraps;

    unsigned int levelSizeX, levelSizeY;
};

#endif // GAMESCREEN_HPP
