#ifndef ERRORSCREENS_HPP
#define ERRORSCREENS_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ErrorScreens
{
    public:
        ErrorScreens() { }

        static void missingResources(sf::RenderWindow &App);
};

#endif /* ERRORSCREENS_HPP */
