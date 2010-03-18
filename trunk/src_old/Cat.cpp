#include <list>
#include "Cat.hpp"
#include "constantes.hpp"
#include "tools/ImageManager.hpp"
#include "CatAStar.hpp"
#include <iostream>

Cat::Cat() : Object(), m_moveClock(), m_cannotMove(0), m_alive(true)
{
    setImage(*gImageManager.getResource(gv.currentTheme+"cat.png"));
}

void Cat::die()
{
    m_alive = false;
    setImage(*gImageManager.getResource(gv.currentTheme+"cheese.png"));
    gv.score += (unsigned int)SCORE_BY_CAT/5;
}

// TODO (Pierre-Yves#2#): [GAMEPLAY] Implémenter l'IA des chats (A*)
void Cat::moveCat(const Level &lvl, const sf::Vector2i &mousePos,
                  const std::vector<Cat> &cats, const bool &random)
{
    if (!m_alive || m_moveClock.GetElapsedTime() < CAT_SPEED)
        return;
    m_moveClock.Reset();
    if (!random)
    {
        std::list<Point> path;
        CatAStar pathfinding(lvl);
        path = pathfinding.aStar(Point(m_pos.x, m_pos.y), Point(mousePos.x, mousePos.y));
        const sf::Vector2i npos(path.begin()->x, path.begin()->y);
        std::cout << npos.x << " " << npos.y << "\n";
        setPosition(npos);
    }
    else
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
                    && temp != mousePos && !catOnTheWay(temp, cats)))
                ok = true;
        }
        if (!ok)
        {
            ++m_cannotMove;
            return;
        }
        setPosition(temp);
        m_cannotMove = 0;
    }
}

void Cat::placeCat(const Level &lvl, const std::vector<Cat> &cats)
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
    std::vector<Cat>::iterator iter = cats.begin();
    for (unsigned int i = 0; i < cats.size(); i++)
    {
        if (iter->pos() == catpos)
            cats.erase(iter);
        else
            ++iter;
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
