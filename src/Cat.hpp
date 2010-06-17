#ifndef CAT_HPP
#define CAT_HPP

#include <list>
#include <vector>
#include "Object.hpp"
#include "Level.hpp"
#include "algorithm/AStarAlgorithm.hpp"

class Cat;

typedef std::vector<Cat> l_cats;

class Cat : public Object
{
    public:
        Cat();
        ~Cat();

        void die();
        bool moveCat(Level &lvl, const sf::Vector2i &mousePos,
                     const l_cats &cats, const bool &astar = false);
        void placeCat(Level &lvl, const l_cats &cats);

        bool isAlive() const { return m_alive; }
        unsigned int cannotMoveNb() const { return m_cannotMove; }

        static void killCat(const sf::Vector2i &catpos, l_cats &cats);
        static bool catOnTheWay(const sf::Vector2i &pos, const l_cats &cats,
                                    const bool &excludeDeadCats = false);

    private:
        bool trapped(Level &lvl, const l_cats &cats) const;
        bool getRandomMove(sf::Vector2i &result, const Level &lvl,
                           const l_cats &cats, const sf::Vector2i &mousePos);
        sf::Clock m_moveClock;
        unsigned int m_cannotMove;
        bool m_alive, m_astarAlreadyMoved;
        cpath path;
};

#endif /* CAT_HPP */
