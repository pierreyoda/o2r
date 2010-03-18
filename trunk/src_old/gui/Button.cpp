#include "Button.hpp"

Button::Button(const std::string text, const sf::Vector2f &pos1, const sf::Vector2f &pos2) :
    m_text(text)
{
    m_text.SetSize(35.f);
	m_text.SetPosition(((pos2.x+pos1.x) / 2 - m_text.GetRect().GetWidth() / 2),
        ((pos2.y+pos1.y) / 2 - m_text.GetRect().GetHeight() / 2));
    float border = 8;
	m_rand = sf::Shape::Rectangle(pos1.x + border, pos1.y + border, pos2.x - border,
        pos2.y - border, sf::Color(0,0,0,0), border, sf::Color(0,0,0,80));
}

bool Button::isMouseOver(const sf::Vector2f &mousePos)
{
	return ((mousePos.x > m_rand.GetPointPosition(0).x && mousePos.x < m_rand.GetPointPosition(2).x) &&
        (mousePos.y > m_rand.GetPointPosition(0).y && mousePos.y < m_rand.GetPointPosition(2).y));
}

void Button::setBorderWidth(const unsigned int &border)
{
    m_rand.SetOutlineWidth(border);
}
