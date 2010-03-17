#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <vector>
#include "Level.hpp"
#include "Cat.hpp"

const sf::Vector2i UP(0, -1);
const sf::Vector2i DOWN(0, 1);
const sf::Vector2i LEFT(-1, 0);
const sf::Vector2i RIGHT(1, 0);

class Mouse : public Object
{
    public:
        Mouse(Level &level, std::vector<Cat> &lcats);

        void move(const sf::Vector2i &dir);

    private:
        sf::Vector2i checkBlocks(const sf::Vector2i &dir) const;
        bool cheesePresent(const sf::Vector2i &pos) const;

        Level &lvl;
        std::vector<Cat> &cats;
};

#endif /* MOUSE_HPP */
