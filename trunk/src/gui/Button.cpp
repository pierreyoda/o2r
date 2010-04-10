#include "Button.hpp"

Button::Button(const std::string &name, const sf::Vector2f &pos,
   const sf::Vector2f &size, const float &border) : m_text(name)
{
	m_rand = sf::Shape::Rectangle(pos.x + border, pos.y + border, size.x-border,
        size.y - border, sf::Color(0,0,0,0), border, sf::Color(0,0,0,80));
    m_text.SetCharacterSize(35);
	m_text.SetPosition((pos.x+border+size.x) / 2 - m_text.GetRect().Width / 3.f,
        (pos.y+border) + m_text.GetRect().Height/2);
}

bool Button::isMouseOver(const sf::Vector2f &mousePos)
{
	return ((mousePos.x > m_rand.GetPointPosition(0).x
          && mousePos.x < m_rand.GetPointPosition(2).x)
         && (mousePos.y > m_rand.GetPointPosition(0).y
         && mousePos.y < m_rand.GetPointPosition(2).y));
}

void Button::setBorderWidth(const unsigned int &border)
{
    m_rand.SetOutlineWidth(border);
}
