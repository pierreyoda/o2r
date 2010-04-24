#include "Level.hpp"
#include "tools/ImageManager.hpp"

using namespace std;

struct upper
{
    int operator()(int c)
    {
        return std::toupper((unsigned char)c);
    }
};

inline void upperworld(string &s)
{
    transform(s.begin(), s.end(), s.begin(), upper());
}

LevelCase::LevelCase(const sf::Vector2i &cpos, const CASETYPE &ctype) :
    character(Level::charToCasetype(ctype)), type(ctype), drawable(cpos)
{
    updateImage();
}

void LevelCase::updateImage()
{
    sf::Image *img = Level::charToImage(character);
    if (img != NULL)
        drawable.setImage(*img);
}

Level::Level(const bool &empty) : cases(), mouseStartPos(0, 0),
    size(DLVL_X, DLVL_Y), randomWallsNb(0), catsNb(DEFAULTNB_OF_CAT),
    levelChanged(true)
{
    if (!empty)
        resetLevel();
    renderTarget.Create(size.x * CASE_SIZE, size.y * CASE_SIZE);
    renderResult.SetImage(renderTarget.GetImage());
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
    for (unsigned int i = 0; i < (unsigned int)size.y; i++)
    {
        cases.push_back(vector<LevelCase>());
        for (unsigned int j = 0; j < (unsigned int)size.x; j++)
            cases[i].push_back(LevelCase(sf::Vector2i(j, i), NOTHING));
    }
    levelChanged = true;
}

void Level::resizeLevel()
{
    resetLevel();
    renderTarget.Create(size.x * CASE_SIZE, size.x * CASE_SIZE);
}

void Level::randomWalls()
{
    static unsigned int limit = nbOfCasetype(NOTHING) + nbOfCasetype(BLOCK);
    for (unsigned int i = 0; i < randomWallsNb; i++)
    {
        sf::Vector2i pos(sf::Randomizer::Random(0, size.x),
                         sf::Randomizer::Random(0, size.y));
        if (getCaseType(pos) == WALL || pos == mouseStartPos)
        {
            if (i >= limit)
                break;
            --i;
            continue;
        }
        setCaseType(pos, WALL);
    }
}

void Level::updateCasesImages()
{
    for (unsigned int i = 0; i < cases.size(); i++)
        for (unsigned int j = 0; j < cases[i].size(); j++)
            cases[i][j].updateImage();
}

const sf::Sprite &Level::getRenderResult(const bool &transparent)
{
    if (levelChanged)
    {
        render(transparent);
        levelChanged = false;
    }
    return renderResult;
}

void Level::render(const bool &transparent)
{
    if (transparent)
        renderTarget.Clear(sf::Color(0, 0, 0, 0));
    else
        renderTarget.Clear();

    for (unsigned int i = 0; i < cases.size(); i++)
    {
        for (unsigned int j = 0; j < cases[i].size(); j++)
        {
            if (transparent && cases[i][j].type == NOTHING);
            else
                renderDrawable(renderTarget, sf::Vector2i(j, i), cases[i][j].type);
        }
    }

    renderTarget.Display();
}

void Level::renderDrawable(sf::RenderTarget &target, const sf::Vector2i &pos,
                           const CASETYPE &type)
{
    if (getCaseType(pos) == UNDEFINED)
        return;
    target.Draw(cases[pos.y][pos.x].drawable.sprite());
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
    if (noCaseThere(pos))
        return;
    cases[pos.y][pos.x].character = casetypeToChar(type);
    cases[pos.y][pos.x].type = type;
    cases[pos.y][pos.x].updateImage();
    levelChanged = true;
}

void Level::setCaseType(const sf::Vector2i &pos, const char &character)
{
    if (noCaseThere(pos))
        return;
    cases[pos.y][pos.x].character = character;
    cases[pos.y][pos.x].type = charToCasetype(character);
    cases[pos.y][pos.x].updateImage();
    levelChanged = true;
}

bool Level::noCaseThere(const sf::Vector2i &pos)
{
    if (pos.y < 0 || pos.y >= (int)cases.size() || pos.x < 0 || pos.x >= (int)cases[0].size())
        return true;
    return false;
}

CASETYPE Level::getCaseType(const sf::Vector2i &pos) const
{
    return getCaseType(pos.x, pos.y);
}

CASETYPE Level::getCaseType(const unsigned int &x, const unsigned int &y) const
{
    if (y < 0 || y >= cases.size() || x < 0 || x >= cases[0].size())
        return UNDEFINED;
    return charToCasetype(cases[y][x].character);
}

sf::Image *Level::charToImage(const char &character)
{
    std::string imgpath = "void.png";
    l_LesElement::iterator iter;
    for (iter = gv.baseLesElements.begin(); iter != gv.baseLesElements.end(); iter++)
        if (character == iter->character)
        {
            imgpath = iter->imagefile;
            break;
        }
    for (iter = gv.lesElements.begin(); iter != gv.lesElements.end(); iter++)
        if (character == iter->character)
        {
            imgpath = iter->imagefile;
            break;
        }
    return gImageManager.getResource(imgpath);
}

CASETYPE Level::charToCasetype(const char &character)
{
    CASETYPE type = NOTHING;
    l_LesElement::iterator iter;
    for (iter = gv.baseLesElements.begin(); iter != gv.baseLesElements.end(); iter++)
        if (character == iter->character)
        {
            type = iter->type;
            break;
        }
    for (iter = gv.lesElements.begin(); iter != gv.lesElements.end(); iter++)
        if (character == iter->character)
        {
            type = iter->type;
            break;
        }
    return type;
}

char Level::casetypeToChar(const CASETYPE &type)
{
    char character = CHAR_NOTHING;
    l_LesElement::iterator iter;
    for (iter = gv.baseLesElements.begin(); iter != gv.baseLesElements.end(); iter++)
        if (type == iter->type)
        {
            character = iter->character;
            break;
        }
    for (iter = gv.lesElements.begin(); iter != gv.lesElements.end(); iter++)
        if (type == iter->type)
        {
            character = iter->character;
            break;
        }
    return character;
}

 CASETYPE Level::stringToCasetype(const std::string &word)
 {
    string temp = word;
    upperworld(temp);
    CASETYPE type = NOTHING;
    if (temp == "BLOCK")
        type = BLOCK;
    else if (temp == "WALL")
        type = WALL;
    else if (temp == "STAIRS")
        type = STAIRS;
    return type;
 }
