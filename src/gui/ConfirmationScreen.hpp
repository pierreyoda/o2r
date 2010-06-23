#ifndef CONFIRMATIONSCREEN_HPP
#define CONFIRMATIONSCREEN_HPP

#include <SFML/Graphics.hpp>

struct ConfirmationScreen
{
    ConfirmationScreen() { }

    static bool askConfirmation(sf::RenderWindow &App, const std::string &text);
};

#endif /* CONFIRMATIONSCREEN_HPP */
