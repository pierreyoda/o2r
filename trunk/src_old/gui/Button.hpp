#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button(const std::string text, const sf::Vector2f &pos1, const sf::Vector2f &pos2);

        bool isMouseOver(const sf::Vector2f &mousePos);

        void setText(const std::string &text) { m_text.SetText(text); }
        void setBorderWidth(const unsigned int &border);
        const sf::String &getString() const { return m_text; }
        const sf::Drawable &getBorder() const { return m_rand; }

    protected:
        sf::Shape m_rand;
        sf::String m_text;
};

#endif /* BUTTON_HPP */
