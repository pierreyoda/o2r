#include "Level.hpp"
#include "tools/ImageManager.hpp"

using namespace std;

Level::Level() : cases(gv.LVL_Y, vector<CASETYPE>(gv.LVL_X, NOTHING)),
    mouseStartPos(0, 0), randomWallsNb(0)
{
    nothingDrawable.setImage(*gImageManager.getResource(gv.currentTheme+"void.png"));
    blockDrawable.setImage(*gImageManager.getResource(gv.currentTheme+"block.png"));
    wallDrawable.setImage(*gImageManager.getResource(gv.currentTheme+"wall.png"));
}

Level::~Level()
{
    clearLevel();
}

void Level::clearLevel()
{
    for (unsigned int i = 0; i < cases.size(); i++)
        cases[i].clear();
    cases.clear();
}

void Level::resetLevel()
{
    clearLevel();
    cases = vector< vector<CASETYPE> > (gv.LVL_Y, vector<CASETYPE>(gv.LVL_X, NOTHING));
}

void Level::resizeLevel()
{
    resetLevel();
}

void Level::randomWalls()
{
    for (unsigned int i = 0; i < randomWallsNb; i++)
    {
        sf::Vector2i pos;
        pos.x = sf::Randomizer::Random(0, gv.LVL_X),
        pos.y = sf::Randomizer::Random(0, gv.LVL_Y);
        if (getCaseType(pos) == WALL || pos == mouseStartPos)
            continue;
        setCaseType(pos, WALL);
    }
}

void Level::render(sf::RenderTarget &target)
{
    for (unsigned int i = 0; i < cases.size(); i++)
    {
        for (unsigned int j = 0; j < cases[i].size(); j++)
            renderDrawable(target, sf::Vector2i(j, i), cases[i][j]);
    }
}

void Level::renderDrawable(sf::RenderTarget &target, const sf::Vector2i &pos,
                           const CASETYPE &type)
{
    if (type == NOTHING)
    {
        nothingDrawable.setPosition(pos);
        target.Draw(nothingDrawable.sprite());
    }
    else if (type == BLOCK)
    {
        blockDrawable.setPosition(pos);
        target.Draw(blockDrawable.sprite());
    }
    else if (type == WALL)
    {
        wallDrawable.setPosition(pos);
        target.Draw(wallDrawable.sprite());
    }
}

unsigned int Level::nbOfCasetype(const CASETYPE &casetype) const
{
    unsigned int nb = 0;
    for (unsigned int i = 0; i < cases.size(); i++)
    {
        for (unsigned int j = 0; j < cases[i].size(); j++)
        {
            if (getCaseType(j, i) == casetype)
                ++nb;
        }
    }
    return nb;
}

void Level::setCaseType(const sf::Vector2i &pos, const CASETYPE &type)
{
    if (pos.y < 0 || pos.y >= (int)cases.size() || pos.x < 0 || pos.x >= (int)cases[0].size())
        return;
    cases[pos.y][pos.x] = type;
}

CASETYPE Level::getCaseType(const sf::Vector2i &pos) const
{
    return getCaseType(pos.x, pos.y);
}

CASETYPE Level::getCaseType(const unsigned int &x, const unsigned int &y) const
{
    if (y < 0 || y >= cases.size() || x < 0 || x >= cases[0].size())
        return NOTHING;
    return cases[y][x];
}
