#include <list>
#include <iostream>
#include "Cat.hpp"
#include "constantes.hpp"
#include "tools/ImageManager.hpp"

Cat::Cat() : Object(), m_moveClock(), m_cannotMove(0), m_alive(true),
    m_astarAlreadyMoved(false)
{
    setImage(*gImageManager.getResource("cat.png"));
}

Cat::~Cat()
{
    path.clear();
}

void Cat::die()
{
    if (!m_alive)
        return;
    m_alive = false;
    setImage(*gImageManager.getResource("cheese.png"));
    gv.score += SCORE_BY_CAT/5;
}

bool Cat::moveCat(Level &lvl, const sf::Vector2i &mousePos,
                  const std::vector<Cat> &cats, const bool &astar)
{
    bool makeRandomMove = false;
    static sf::Vector2i prevMousepos = mousePos;

    if (!m_alive || m_moveClock.GetElapsedTime() < CAT_SPEED)
        return false;
    m_moveClock.Reset();

    if (astar)
    {
        if (!m_astarAlreadyMoved || (mousePos != prevMousepos || lvl.hasChanged()))
        {
            path = *AStarAlgorithm::pathfinding(m_pos, mousePos, lvl);
            prevMousepos = mousePos;
            m_astarAlreadyMoved = true;
        }
        if (!path.empty())
        {
            sf::Vector2i npos(*path.begin());
            path.pop_front();
            if (!catOnTheWay(npos, cats) && lvl.getCaseType(npos) == NOTHING)
                setPosition(npos);
            if (npos == mousePos)
                return true;
            m_cannotMove = 0;
        }
        else
            makeRandomMove = true;
        if (!makeRandomMove && trapped(lvl, cats))
        {
            ++m_cannotMove;
            return false;
        }
    }
    if (!astar || makeRandomMove)
    {
        static const unsigned int tries = 10;
        sf::Vector2i offset(0, 0), temp(m_pos);
        bool ok = false;
        for (unsigned int i = 0; i < tries && !ok; i++)
        {
            offset.x = sf::Randomizer::Random(-1, 1),
            offset.y = sf::Randomizer::Random(-1, 1);
            temp = m_pos + offset;
            if (!Cat::outOfScreen(temp) && (lvl.getCaseType(temp) == NOTHING
                    && !catOnTheWay(temp, cats)))
                ok = true;
        }
        if (!ok)
        {
            ++m_cannotMove;
            return false;
        }
        setPosition(temp);
        if (temp == mousePos)
            return true;
        m_cannotMove = 0;
    }
    return false;
}

void Cat::placeCat(Level &lvl, const std::vector<Cat> &cats)
{
    bool done = false;
    sf::Vector2i pos;
    const unsigned int nbOfFreeCases = lvl.nbOfCasetype(NOTHING);
    for (unsigned int i = 0; i < nbOfFreeCases && !done; i++)
    {
        pos.x = sf::Randomizer::Random(0, gv.LVL_X-1),
        pos.y = sf::Randomizer::Random(0, gv.LVL_Y-1);
        bool ok = !catOnTheWay(pos, cats);
        if (ok && lvl.getCaseType(pos) == NOTHING && lvl.getMouseStartPos() != pos)
            done = true;
    }
    setPosition(pos);
}

void Cat::killCat(const sf::Vector2i &catpos, std::vector<Cat> &cats)
{
    static std::vector<Cat>::iterator iter = cats.begin();
    for (iter = cats.begin(); iter != cats.end(); iter++)
    {
        if (iter->pos() == catpos)
        {
            cats.erase(iter);
            break;
        }
    }
}

bool Cat::catOnTheWay(const sf::Vector2i &pos, const std::vector<Cat> &cats,
                      const bool &excludeDeadCats)
{
    for (unsigned int i = 0; i < cats.size(); i++)
    {
        if (pos == cats[i].pos())
        {
            if (excludeDeadCats && !cats[i].isAlive())
                return false;
            return true;
        }
    }
    return false;
}

bool Cat::trapped(Level &lvl, const l_cats &cats) const
{
    unsigned int blockedCount = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (j != 0 && (lvl.getCaseType(i, j) != NOTHING ||
                           catOnTheWay(sf::Vector2i(i, j), cats)))
                ++blockedCount;
        }
    }
    return (blockedCount == 8);
}
