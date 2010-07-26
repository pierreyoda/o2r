#include "Object.hpp"
#include "GlobalVariables.hpp"

Object::Object(const sf::Vector2i &ipos) : m_pos(ipos)
{
    updatePosition();
    setImage(gImageManager.getResource("void.png"));
}

void Object::setImage(sf::Image *img)
{
    if (img == 0)
        return;
    m_sprite.SetImage(*img);
    if (ORIGIN_AT_CENTER)
        m_sprite.SetOrigin(img->GetWidth()/2.f, m_sprite.GetSize().y/2.f);
}

void Object::setPosition(const sf::Vector2i &npos)
{
    m_pos = npos;
    updatePosition();
}

void Object::updatePosition()
{
    m_sprite.SetPosition(m_pos.x * CASE_SIZE, m_pos.y * CASE_SIZE);
    if (ORIGIN_AT_CENTER)
        m_sprite.Move(CASE_SIZE/2, CASE_SIZE/2);
}

bool Object::outOfScreen(const sf::Vector2i &pos, const sf::Vector2i &screenSize)
{
    return outOfScreen(pos.x, pos.y, screenSize);
}

bool Object::outOfScreen(const unsigned int &x, const unsigned int &y,
                         const sf::Vector2i &screenSize)
{
    return (x < 0 || x >= (unsigned int)screenSize.x
            || y < 0 || y >= (unsigned int)screenSize.y);
}
