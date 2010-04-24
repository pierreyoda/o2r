#include "Mouse.hpp"
#include "constantes.hpp"

Mouse::Mouse(levelPtr &level, l_cats &lcats) : Object(), lvl(level), cats(lcats),
    m_remainingLifes(DEFAULT_NB_OF_LIFES), m_dead(false)
{
    setImage(*gImageManager.getResource("mouse.png"));
}

Mouse::~Mouse()
{

}

void Mouse::die()
{
    if (m_remainingLifes >= 1)
    {
        --m_remainingLifes;
        respawn();
    }
    else
        m_dead = true;
}

void Mouse::revive()
{
    m_remainingLifes = DEFAULT_NB_OF_LIFES;
    m_dead = false;
}

bool Mouse::move(const sf::Vector2i &dir)
{
    const sf::Vector2i pos = m_pos + dir;
    const CASETYPE casetype = lvl->getCaseType(pos);
    if (outOfScreen(pos, lvl->getSize()) || Cat::catOnTheWay(pos, cats, true)
            || casetype == WALL)
        return false;
    if (casetype == BLOCK)
    {
        sf::Vector2i endblocks = checkBlocks(dir);
        if (outOfScreen(endblocks, lvl->getSize())
                || lvl->getCaseType(endblocks) != NOTHING
                || Cat::catOnTheWay(endblocks, cats, true))
            return false;
        if (cheesePresent(endblocks))
            Cat::killCat(endblocks, cats);
        lvl->setCaseType(pos, NOTHING);
        lvl->setCaseType(endblocks, BLOCK);
    }
    if (cheesePresent(pos))
    {
        Cat::killCat(pos, cats);
        gv.score += SCORE_BY_CAT;
    }
    setPosition(pos);
    if (casetype == STAIRS)
        return true;
    return false;
}

bool compareSecurityLevel(posSecurityValue a, posSecurityValue b)
{
    return (a.second < b.second);
}

void Mouse::respawn(const unsigned int &securityLevel)
{
    std::vector<posSecurityValue> positions;
    for (unsigned int i = 0; i < securityLevel; i++)
    {
        int x = sf::Randomizer::Random(0, lvl->getSize().x),
            y = sf::Randomizer::Random(0, lvl->getSize().y);
        sf::Vector2i pos(x, y);
        if (lvl->getCaseType(pos) == NOTHING && !Cat::catOnTheWay(pos, cats)
            && !trappedByWalls(pos))
        positions.push_back(posSecurityValue(pos, estimatePosSecurity(pos)));
    }
    sort(positions.begin(), positions.end(), compareSecurityLevel);
    setPosition(positions[0].first);
}

sf::Vector2i Mouse::checkBlocks(const sf::Vector2i &dir) const
{
    sf::Vector2i temp = m_pos + dir;
    bool xmove = (dir == LEFT || dir == RIGHT);
    while (!outOfScreen(temp, lvl->getSize()) && lvl->getCaseType(temp) == BLOCK)
    {
        if (xmove)
        {
            if (dir.x < 0)
                --temp.x;
            else
                ++temp.x;
        }
        else
        {
            if (dir.y < 0)
                --temp.y;
            else
                ++temp.y;
        }
    }
    return temp;
}

bool Mouse::cheesePresent(const sf::Vector2i &pos) const
{
    return (Cat::catOnTheWay(pos, cats) && !Cat::catOnTheWay(pos, cats, true));
}

bool Mouse::trappedByWalls(const sf::Vector2i &pos) const
{
    unsigned int wallsCount = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (j != 0 && lvl->getCaseType(i, j) == WALL)
                ++wallsCount;
        }
    }
    return (wallsCount == 8);
}

unsigned int Mouse::estimatePosSecurity(const sf::Vector2i &pos) const
{
    unsigned int totalPound = 0;
    for (unsigned int i = 0; i < cats.size(); i++)
        totalPound += AStarAlgorithm::pound(m_pos, cats[i].pos());
    return totalPound;
}
