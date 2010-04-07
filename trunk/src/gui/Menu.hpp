#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

typedef bool (*pRunFonction)(sf::RenderWindow&);
typedef std::pair<Button, pRunFonction> menuButton;

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        virtual void initialize() { };
        bool run(sf::RenderWindow &App);

    protected:
        std::vector<menuButton> buttons;
};

struct MainMenu : public Menu
{
    MainMenu();

    void initialize();
};

#endif /* MENU_HPP */
