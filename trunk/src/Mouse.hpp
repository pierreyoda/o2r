#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <vector>
#include "Level.hpp"
#include "Cat.hpp"

const sf::Vector2i UP(0, -1);
const sf::Vector2i DOWN(0, 1);
const sf::Vector2i LEFT(-1, 0);
const sf::Vector2i RIGHT(1, 0);

typedef std::pair<sf::Vector2i, unsigned int> posSecurityValue;

class Mouse : public Object
{
    public:
        Mouse(levelPtr &level, std::vector<Cat> &lcats);
        ~Mouse();

        void die();
        void revive();
        bool move(const sf::Vector2i &dir);
        void updateLevelPtr(levelPtr &level) { lvl = level; }

        bool dead() const { return m_dead; }
        unsigned int remainingLifes() const { return m_remainingLifes; }

    private:
        void respawn(const unsigned int &securityLevel = DEFAULT_RESPAWN_SECURITYLVL);
        sf::Vector2i checkBlocks(const sf::Vector2i &dir) const;
        bool cheesePresent(const sf::Vector2i &pos) const;
        bool trappedByWalls(const sf::Vector2i &pos) const;
        unsigned int estimatePosSecurity(const sf::Vector2i &pos) const;

        levelPtr lvl;
        l_cats &cats;
        unsigned int m_remainingLifes;
        bool m_dead;
};

#endif /* MOUSE_HPP */
