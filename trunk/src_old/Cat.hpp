#ifndef CAT_HPP
#define CAT_HPP

#include <vector>
#include "Object.hpp"
#include "Level.hpp"

class Cat : public Object
{
    public:
        Cat();

        void die();
        void moveCat(const Level &lvl, const sf::Vector2i &mousePos,
                     const std::vector<Cat> &cats, const bool &random = false);
        void placeCat(const Level &lvl, const std::vector<Cat> &cats);

        bool isAlive() const { return m_alive; }
        unsigned int cannotMoveNb() const { return m_cannotMove; }

        static void killCat(const sf::Vector2i &catpos, std::vector<Cat> &cats);
        static bool catOnTheWay(const sf::Vector2i &pos, const std::vector<Cat> &cats,
                                    const bool &excludeDeadCats = false);

    private:
        sf::Clock m_moveClock;
        unsigned int m_cannotMove;
        bool m_alive;
};

#endif /* CAT_HPP */
