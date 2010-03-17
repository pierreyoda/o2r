#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TextBox
{
    public:
        TextBox(const unsigned int limit = 0, const std::string &ctext = "");

        void center(const sf::Vector2f &screen);
        void clearText();
        void setPosition(const sf::Vector2f &pos) { box.SetPosition(pos); }
        void setPosition(const float &x, const float &y) { box.SetPosition(x, y); }
        void onTextEntered(const unsigned short &unicode);

        const sf::String &getString() const { return box; }
        std::string getText() const { return text; }

    private:
        std::string text;
        sf::String box;
        unsigned int textLimit;
};

#endif /* TEXTBOX_HPP */
