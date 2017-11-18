#include "HudRectangle.hpp"
#include "../GameCanvas.hpp"

const sf::Color FILL_COLOR(150, 150, 150);
const unsigned int HudRectangle::HEIGHT = 60;

HudRectangle::HudRectangle()
{
    mRectangleShape.setFillColor(FILL_COLOR);
}

void HudRectangle::setWidth(unsigned int width)
{
    mRectangleShape.setSize(sf::Vector2f(width, HEIGHT));
}

void HudRectangle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mRectangleShape, states);
}
