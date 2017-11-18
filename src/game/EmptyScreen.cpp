#include <SFML/Graphics.hpp>
#include "EmptyScreen.hpp"

EmptyScreen::EmptyScreen(const sf::Window &window) : Screen(window)
{

}

void EmptyScreen::render(sf::RenderTarget &target, sf::RenderStates states)
{

}

void EmptyScreen::update(const sf::Time &dt)
{

}

void EmptyScreen::handleEvent(const sf::Event &event)
{

}

bool EmptyScreen::start(TiledMapPtr level)
{
    return Screen::start(level);
}
