#include "Menu.hpp"

using namespace sf;

Menu::Menu()
{
    initialize();
}

Menu::~Menu()
{

}

bool Menu::run(RenderWindow &App)
{
    bool run = true;
    static const Input &Input = App.GetInput();
    while (App.IsOpened() && run)
    {

    }
    return false;
}
