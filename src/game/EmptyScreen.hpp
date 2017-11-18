#ifndef EMPTYSCREEN_HPP
#define EMPTYSCREEN_HPP

#include "Screen.hpp"

/** Empty screen.
*@todo Add "demo" feature = random level with AI entities moving around?
*/
class EmptyScreen : public Screen
{
public:
    EmptyScreen(const sf::Window &window);

    void render(sf::RenderTarget &target,
                sf::RenderStates states = sf::RenderStates::Default);

    void update(const sf::Time &dt);

    void handleEvent(const sf::Event &event);

    bool start(TiledMapPtr level);
};

#endif // EMPTYSCREEN_HPP
