#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "HudManager.hpp"

typedef bool (*pRunFonction)();
typedef std::pair<Button, pRunFonction*> menuButton;

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        void addButton(const Button &button);
        void connectButton(const unsigned int &id, pRunFonction function);
        bool run(sf::RenderWindow &App, HudManager &hud);

    private:
        std::vector<menuButton> m_buttons;
};

#endif /* MENU_HPP */
