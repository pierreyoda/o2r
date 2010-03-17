#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TextBox
{
    public:
        TextBox(const unsigned int &limit = 0, const std::string &ctext = "");

        void center(const sf::Vector2f &screen);
        void clearText();
        void setPosition(const sf::Vector2f &pos) { box.SetPosition(pos); }
        void setPosition(const float &x, const float &y) { box.SetPosition(x, y); }
        void onTextEntered(const unsigned short &unicode);

        std::string getString() const { return text; }
        const sf::Text &getText() const { return box; }

    private:
        std::string text;
        sf::Text box;
        unsigned int caractersLimit;
};

#endif /* TEXTBOX_HPP */
