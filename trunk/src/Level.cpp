#include <iostream>
#include <fstream>
#include <sstream>
#include "Level.hpp"
#include "tools/ImageManager.hpp"

using namespace std;

const string levelSizeX = "X=";
const string levelSizeY = "Y=";
const string nbOfRandomWalls = "RandomWalls=";
const string nbOfCats = "NbOfCats=";
const sf::Color BACKGROUND_COLOR(128, 128, 0);

struct upper
{
    int operator()(int c)
    {
        return toupper((unsigned char)c);
    }
};

inline void upperworld(string &s)
{
    transform(s.begin(), s.end(), s.begin(), upper());
}

LevelCase::LevelCase(const sf::Vector2i &cpos, const char &character) :
    character(character), type(Level::charToCasetype(character)), drawable(cpos)
{
    updateImage();
}

void LevelCase::updateImage()
{
    sf::Image *img = Level::charToImage(character);
    if (img != NULL)
        drawable.setImage(*img);
}

Level::Level(const string &file, const string &name) : cases()
{
    if (name.empty())
        infos.name = file;
    else
        infos.name = name;
    infos.filename = file, infos.randomWallsNb = 0, infos.hasChanged = true;
    infos.iCatsNb = infos.catsNb = DEFAULTNB_OF_CAT;
    if (file == emptyLevelName || !readLevelFile())
        fillWithNothingType();

    renderTarget.Create(infos.size.x * CASE_SIZE, infos.size.y * CASE_SIZE);
    renderResult.SetImage(renderTarget.GetImage());
}

Level::~Level()
{

}

bool Level::writeLevel(const string &filename)
{
    if (filename.empty())
        return false;
    infos.filename = infos.name =  filename;

    cout << "Writing current level to '" << filename << "'.\n";
    ofstream file(filename.c_str(), ios::out | ios::trunc);
    if (!file)
        return false;

    file << levelSizeX << infos.size.x << "\n" << levelSizeY << infos.size.y << "\n";
    for (unsigned int i = 0; i < cases.size(); i++)
    {
        for (unsigned int j = 0; j < cases[i].size(); j++)
        {
            if (sf::Vector2i(j, i) == infos.mouseStartPos)
                file << CHAR_MOUSE;
            else
                file << cases[i][j].character;
        }
        file << "\n";
    }
    file << nbOfRandomWalls << infos.randomWallsNb << "\n"
        <<  nbOfCats << infos.iCatsNb;

    return true;
}

bool Level::readLevelFile()
{
    cout << "Reading level '" << infos.filename << "'.\n";
    string line;
    ifstream file(infos.filename.c_str(), ios::in);
    if (!file)
        return false;
    unsigned int gap = 0;
    if (infos.size.x == 0 || infos.size.y == 0)
        infos.size.x = DLVL_X, infos.size.y = DLVL_Y;
    sf::Vector2i oldSize(infos.size);
    for (unsigned int i = 0; getline(file, line); i++)
    {
        if (!analyseLevelFileLine(line, i, oldSize, gap))
            return false;
    }
    return true;
}

bool Level::analyseLevelFileLine(const string &line, const unsigned int &linenb,
                                 const sf::Vector2i &oldSize, unsigned int &gap)
{
    if (linenb < 2)
    {
        if (setSizeFromLine(line, oldSize))
            ++gap;
        return true;
    }
    if (linenb >= infos.size.y+gap)
    {
        if (line.substr(0, nbOfRandomWalls.size()) == nbOfRandomWalls)
            setNbOfRandomWallsFromText(line.substr(nbOfRandomWalls.size(),
                                                     line.size()));
        else if (line.substr(0, nbOfCats.size()) == nbOfCats)
            setiNbOfCatsFromText(line.substr(nbOfCats.size(), line.size()));
        return true;
    }
    cases.push_back(vector<LevelCase>());
    for (unsigned int i = 0; i < line.size(); i++)
    {
        sf::Vector2i pos(i, linenb-gap);
        if (line[i] == CHAR_MOUSE)
        {
            infos.mouseStartPos = pos;
            cases[linenb-gap].push_back(LevelCase(pos, CHAR_NOTHING));
        }
        else
            cases[linenb-gap].push_back(LevelCase(pos, line[i]));
    }

    if (linenb == infos.size.y+gap-1)
        gap = 0;
    return true;
}

bool Level::setSizeFromLine(const string &line, const sf::Vector2i &oldSize)
{
    unsigned int size = 0;
    if (line.substr(0, levelSizeX.size()) == levelSizeX)
    {
        size = gv.textToNb(line.substr(levelSizeX.size(), line.size()));
        if (size > 0)
        {
            if (size != (unsigned int)oldSize.x)
                cout << "X size set to " << size << ".\n";
            infos.size.x = size;
        }
    }
    else if (line.substr(0, levelSizeY.size()) == levelSizeY)
    {
        size = gv.textToNb(line.substr(levelSizeY.size(), line.size()));
        if (size > 0)
        {
            if (size != (unsigned int)oldSize.y)
                cout << "Y size set to " << size << ".\n";
            infos.size.y = size;
        }
    }
    if (size > 0)
    {
        gv.resizeGame();
        return true;
    }
    return false;
}

void Level::setiNbOfCatsFromText(const string &text)
{
    unsigned int number = gv.textToNb(text);
    if (number < 0 || number > nbOfCasetype(NOTHING))
        return;
    infos.iCatsNb = infos.catsNb = number;
    cout << "Number of cats set to " << number << " for this level.\n";
}

void Level::setNbOfRandomWallsFromText(const string &text)
{
    unsigned int number = gv.textToNb(text);
    if (number == 0)
        return;
    if (number < 0 || number > (unsigned int)infos.size.x*infos.size.y)
        return;
    infos.randomWallsNb = number;
    cout << "Number of random walls set to " << number << " for this level.\n";
}

void Level::fillWithNothingType()
{
    for (unsigned int i = 0; i < cases.size(); i++)
        cases[i].clear();
    cases.clear();

    infos.size.x = DLVL_X, infos.size.y = DLVL_Y;
    for (unsigned int i = 0; i < (unsigned int)infos.size.y; i++)
    {
        cases.push_back(vector<LevelCase>());
        for (unsigned int j = 0; j < (unsigned int)infos.size.x; j++)
            cases[i].push_back(LevelCase(sf::Vector2i(j, i), NOTHING));
    }
    infos.hasChanged = true;
}

void Level::randomWalls()
{
    static unsigned int limit = nbOfCasetype(NOTHING) + nbOfCasetype(BLOCK);
    for (unsigned int i = 0; i < infos.randomWallsNb; i++)
    {
        sf::Vector2i pos(sf::Randomizer::Random(0, infos.size.x),
                         sf::Randomizer::Random(0, infos.size.y));
        if (getCaseType(pos) == WALL || pos == infos.mouseStartPos)
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
    if (infos.hasChanged)
    {
        render(transparent);
        infos.hasChanged= false;
    }
    return renderResult;
}

void Level::render(const bool &transparent)
{
    if (transparent)
        renderTarget.Clear(sf::Color(0, 0, 0, 0));
    else
        renderTarget.Clear(BACKGROUND_COLOR);

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
    infos.hasChanged= true;
}

void Level::setCaseType(const sf::Vector2i &pos, const char &character)
{
    setCaseType(pos, charToCasetype(character));
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
    string imgpath = "void.png";
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

 CASETYPE Level::stringToCasetype(const string &word)
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
