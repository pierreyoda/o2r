#include "Button.hpp"

const sf::Color BUTTON_DEFAULT_COLOR(0,0,0,80);

Button::Button(const std::string &name, const sf::Vector2f &pos,
   const sf::Vector2f &size, const float &border) : m_text(name)
{
	m_rand = sf::Shape::Rectangle(pos.x + border, pos.y + border, size.x-border,
        size.y - border, sf::Color(0,0,0,0), border, BUTTON_DEFAULT_COLOR);
    m_text.SetCharacterSize(35);
    float posX = (pos.x+border+size.x) / 2.f;
    if (name.size() > 5)
        posX -= m_text.GetRect().Width / 3.f;
    else if (size.x <= BUTTON_HALF_SIZE.x)
        posX += m_text.GetRect().Width;
	m_text.SetPosition(posX, (pos.y+border) + m_text.GetRect().Height/2);

    adjustText(pos.x, size.x);
}

Button::Button(const std::string &name, const float &y, const sf::Vector2f &size,
               const float &border) : m_text(name)
{
    const float &x = gv.SCREEN_W / 2 - size.x / 2;
    m_rand = sf::Shape::Rectangle(x + border, y + border, size.x-border,
        size.y - border, sf::Color(0,0,0,0), border, BUTTON_DEFAULT_COLOR);
    m_text.SetCharacterSize(35);
    m_text.SetPosition((x+border+size.x) / 2 - m_text.GetRect().Width / 3.f,
        (y+border) + m_text.GetRect().Height/2);

    adjustText(x, size.x);
}

void Button::adjustText(const float &posx, const float &sizex)
{
    unsigned int security = 0;
    while (security < 100 &&
        m_text.GetPosition().x + m_text.GetRect().Width >= posx + sizex)
    {
        m_text.Move(-1.f, 0.f);
        ++security;
    }
    m_text.Move(-5.f, 0.f);
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
