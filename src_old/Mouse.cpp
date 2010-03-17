#include "Mouse.hpp"
#include "constantes.hpp"

Mouse::Mouse(Level &level, std::vector<Cat> &vcats) : Object(),
    lvl(level), cats(vcats)
{
    setImage(*gImageManager.getResource(gv.currentTheme+"mouse.png"));
}

void Mouse::move(const sf::Vector2i &dir)
{
    const sf::Vector2i pos = m_pos + dir;
    const CASETYPE casetype = lvl.getCaseType(pos);
    if (outOfScreen(pos) || Cat::catOnTheWay(pos, cats, true) || casetype == WALL)
        return;
    if (casetype == BLOCK)
    {
        sf::Vector2i endblocks = checkBlocks(dir);
        if (outOfScreen(endblocks) || lvl.getCaseType(endblocks) != NOTHING
                || Cat::catOnTheWay(endblocks, cats, true))
            return;
        if (cheesePresent(endblocks))
            Cat::killCat(endblocks, cats);
        lvl.setCaseType(pos, NOTHING);
        lvl.setCaseType(endblocks, BLOCK);
    }
    if (cheesePresent(pos))
    {
        Cat::killCat(pos, cats);
        gv.score += SCORE_BY_CAT;
    }
    setPosition(pos);
}

sf::Vector2i Mouse::checkBlocks(const sf::Vector2i &dir) const
{
    sf::Vector2i temp = m_pos + dir;
    bool xmove = (dir == LEFT || dir == RIGHT);
    while (!outOfScreen(temp) && lvl.getCaseType(temp) == BLOCK)
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
