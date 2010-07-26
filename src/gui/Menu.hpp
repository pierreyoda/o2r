#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextBox.hpp"
#include "HudManager.hpp"

typedef boost::function<void()> bRunFonction;
typedef std::pair<Button, bRunFonction> menuButton;

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        void addButton(const Button &button, bRunFonction fonction = 0,
            const bool &write = false);
        void connectButton(const unsigned int &id, bRunFonction function);
        bool run(sf::RenderWindow &App, HudManager &hud, bool &resume,
            const std::string &defaultTextForTextfield = "");

        std::string currentString() const { return text.getString(); }

    private:
        std::vector<menuButton> m_buttons;
        std::vector<bool> m_writeButtons;
        TextBox text;
};

#endif /* MENU_HPP */
