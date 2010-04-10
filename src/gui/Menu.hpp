#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "HudManager.hpp"

typedef void (*pRunFonction)();
typedef boost::function<void()> bRunFonction;
typedef std::pair<Button, bRunFonction> menuButton;

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        void addButton(const Button &button);
        void connectButton(const unsigned int &id, bRunFonction function);
        bool run(sf::RenderWindow &App, HudManager &hud);

    private:
        std::vector<menuButton> m_buttons;
};

#endif /* MENU_HPP */
