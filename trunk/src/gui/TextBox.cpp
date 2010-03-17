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
    box.SetString(text);
}

void TextBox::center(const sf::Vector2f &screen)
{
    box.SetX(screen.x/2 - box.GetRect().GetSize().x/2);
}

void TextBox::clearText()
{
    text.clear();
    box.SetString("");
}
