#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "../GlobalVariables.hpp"

const sf::Vector2f BUTTON_DEFAULT_SIZE(250, 100);
const sf::Vector2f BUTTON_WIDE_SIZE(300, 100);
const sf::Vector2f BUTTON_HALF_SIZE(145, 100);

class Button
{
    public:
        Button(const std::string &name, const sf::Vector2f &pos,
                const sf::Vector2f &size = BUTTON_DEFAULT_SIZE,
                const float &border = BUTTON_DEFAULT_BORDER);
        Button(const std::string &name, const float &y,
                const sf::Vector2f &size = BUTTON_DEFAULT_SIZE,
                const float &border = BUTTON_DEFAULT_BORDER);

        bool isMouseOver(const sf::Vector2f &mousePos);

        void setText(const std::string &text) { m_text.SetString(text); }
        void setBorderWidth(const unsigned int &border);
        const sf::Drawable &getText() const { return m_text; }
        const sf::Drawable &getBorder() const { return m_rand; }

    private:
        void adjustText(const float &posx, const float &sizex);

        sf::Shape m_rand;
        sf::Text m_text;
};

#endif /* BUTTON_HPP */
