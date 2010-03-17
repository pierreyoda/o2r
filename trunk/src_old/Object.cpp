#include "Object.hpp"
#include "constantes.hpp"

Object::Object(const sf::Vector2i &ipos) : m_pos(ipos)
{
    updatePosition();
    setImage(*gImageManager.getResource(gv.currentTheme + "void.png"));
}

void Object::setImage(sf::Image &img)
{
    m_sprite.SetImage(img);
    m_sprite.SetCenter(img.GetWidth()/2.f, m_sprite.GetSubRect().GetHeight()/2.f);
}

void Object::setPosition(const sf::Vector2i &npos)
{
    m_pos = npos;
    updatePosition();
}

void Object::updatePosition()
{
    m_sprite.SetPosition(m_pos.x * CASE_SIZE, m_pos.y * CASE_SIZE);
    m_sprite.Move(CASE_SIZE/2, CASE_SIZE/2);
}

bool Object::collideWith(const Object &object) const
{
    return collideWith(object.m_pos);
}

bool Object::collideWith(const sf::Vector2i &pos) const
{
    return (m_pos == pos);
}

bool Object::outOfScreen(const sf::Vector2i &pos)
{
    return outOfScreen(pos.x, pos.y);
}

bool Object::outOfScreen(const unsigned int &x, const unsigned int &y)
{
    return (x < 0 || x > gv.LVL_X-1 || y < 0 || y > gv.LVL_Y-1);
}
