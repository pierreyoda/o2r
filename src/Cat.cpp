#include <list>
#include <iostream>
#include "Cat.hpp"
#include "Mouse.hpp"
#include "constantes.hpp"
#include "tools/ImageManager.hpp"

Cat::Cat() : Object(), m_moveClock(), m_cannotMove(0), m_alive(true),
    m_astarAlreadyMoved(false)
{
    setImage(gImageManager.getResource("cat.png"));
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
    setImage(gImageManager.getResource("cheese.png"));
    gv.score += SCORE_BY_CAT/5;
}

bool Cat::moveCat(Level &lvl, const sf::Vector2i &mousePos,
                  const l_cats &cats, const bool &astar)
{
    bool makeRandomMove = false;
    const LevelInformations &infos = lvl.getInfos();
    static sf::Vector2i prevMousepos = mousePos;

    if (!m_alive || m_moveClock.GetElapsedTime() < CAT_SPEED)
        return false;
    m_moveClock.Reset();

    if (astar)
    {
        if (!m_astarAlreadyMoved || (mousePos != prevMousepos || infos.hasChanged))
        {
            path l= *AStarAlgorithm::pathfinding(m_pos, mousePos, lvl);
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
        sf::Vector2i npos;
        if (!getRandomMove(npos, lvl, cats, mousePos))
        {
            ++m_cannotMove;
            return false;
        }
        setPosition(npos);
        if (npos == mousePos)
            return true;
        m_cannotMove = 0;
    }
    return false;
}

void Cat::placeCat(Level &lvl, const l_cats &cats)
{
    bool done = false;
    sf::Vector2i pos;
    const LevelInformations &infos = lvl.getInfos();
    const unsigned int nbOfFreeCases = lvl.nbOfCasetype(NOTHING);
    for (unsigned int i = 0; i < nbOfFreeCases && !done; i++)
    {
        pos.x = sf::Randomizer::Random(0, infos.size.x-1),
        pos.y = sf::Randomizer::Random(0, infos.size.y-1);
        bool ok = !catOnTheWay(pos, cats);
        if (ok && lvl.getCaseType(pos) == NOTHING && infos.mouseStartPos != pos)
            done = true;
    }
    setPosition(pos);
}

void Cat::killCat(const sf::Vector2i &catpos, l_cats &cats)
{
    static l_cats::iterator iter = cats.begin();
    for (iter = cats.begin(); iter != cats.end(); iter++)
    {
        if (iter->pos() == catpos)
        {
            cats.erase(iter);
            break;
        }
    }
}

bool Cat::catOnTheWay(const sf::Vector2i &pos, const l_cats &cats,
                      const bool &excludeDeadCats)
{
    l_cats::const_iterator iter;
    for (iter= cats.begin(); iter != cats.end(); iter++)
    {
        if (pos == iter->pos())
        {
            if (excludeDeadCats && !iter->isAlive())
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

bool whatIsBetterCaseForCat(const posSecurityValue &a, const posSecurityValue &b)
{
    return (a.second < b.second);
}

bool Cat::getRandomMove(sf::Vector2i &result, const Level &lvl,
                        const l_cats &cats, const sf::Vector2i &mousePos)
{
    std::list<posSecurityValue> l_pounds;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            sf::Vector2i pos(m_pos.x+i, m_pos.y+j);
            if (pos == m_pos || outOfScreen(pos, lvl.getInfos().size)
                    || lvl.getCaseType(pos) != NOTHING
                    || catOnTheWay(pos, cats))
                continue;
            l_pounds.push_back(posSecurityValue(pos,
                                                AStarAlgorithm::pound(pos, mousePos)));
        }
    }
    if (l_pounds.empty())
        return false;
    l_pounds.sort(whatIsBetterCaseForCat);
    if (l_pounds.begin() != l_pounds.end())
    {
        result = l_pounds.begin()->first;
        return true;
    }
    return false;
}
