#include "TextBox.hpp"

using namespace sf;

TextBox::TextBox(const unsigned int &limit, const std::string &ctext)  :
    text(ctext), box(ctext), caractersLimit(limit)
{

}

void TextBox::onTextEntered(const unsigned short &unicode)
{
    if (unicode == 8) // Backspace
        text = text.substr(0, text.size() - 1);
    else  if ((unicode >= 32 && unicode <= 126) || (unicode >= 192 && unicode <= 255))
    {
        if (caractersLimit == 0 || text.size()+1 <= caractersLimit)
            text += (char)unicode; // Letter
    }
    updateText();
}

void TextBox::center(const sf::Vector2f &screen)
{
    box.SetX(screen.x/2 - box.GetRect().Width/2);
}

void TextBox::updateText()
{
    box.SetString(text);
}

void TextBox::clearString()
{
    text.clear();
    updateText();
}

void TextBox::setString(const std::string &nstring)
{
    if (caractersLimit > 0)
        text = nstring.substr(0, caractersLimit);
    else
        text = nstring;
    updateText();
}
