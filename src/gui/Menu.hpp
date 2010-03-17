#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        bool run(sf::RenderWindow &App, std::string &string);

    protected:
        std::vector<Button> buttons;
};

#endif /* MENU_HPP */
