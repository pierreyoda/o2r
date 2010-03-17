#include <iostream>
#include <fstream>
#include <sstream>
#include "LevelFileInterpreter.hpp"

using namespace std;

const string levelSizeX = "X=";
const string levelSizeY = "Y=";
const string nbOfRandomWalls = "RandomWalls=";
const string nbOfCats = "NbOfCats=";
const string newVersion = "# Open Rodent's Revenge";

bool LevelFileInterpreter::writeLevel(Level &level, const string &filename,
                                      const bool &oldmethod)
{
    cout << "Writing level '" << filename << "'.\n";
    ofstream file(filename.c_str(), ios::out | ios::trunc);
    if (!file)
        return false;

    /*if (!oldmethod)
        file << newVersion << "\n";*/
    file << levelSizeX << gv.nbToText(gv.LVL_X) << "\n"
           << levelSizeY << gv.nbToText(gv.LVL_Y) << "\n";
    for (unsigned int i = 0; i < level.content().size(); i++)
    {
        for (unsigned int j = 0; j < level.content()[i].size(); j++)
        {
            if (level.getMouseStartPos() == sf::Vector2i(j, i))
                file << CHAR_MOUSE;
            else
                file << casetypeToChar(level.content()[i][j].type);
        }
        file << "\n";
    }

    return true;
}

bool LevelFileInterpreter::readLevel(Level &level, const string &filename)
{
    cout << "Reading level '" << filename << "'.\n";
    string line;
    bool oldVersion = true;
    ifstream file(filename.c_str(), ios::in);
    if (!file)
        return false;
    level.setNbOfRandomWalls(0);
    level.setNbOfCats(DEFAULTNB_OF_CAT);
    for (unsigned int i = 0; getline(file, line); i++)
    {
        bool ok = true;
        if (i == 0 && line == newVersion)
        {
            oldVersion = false;
            continue;
        }
        ok = analyseLine(level, line, i, false);
        if (!ok)
            return true;
    }
    return true;
 }

bool LevelFileInterpreter::analyseLine(Level &level,  const string &line,
                            const unsigned int &linenb, const bool &old)
{
    static unsigned int gap = 0;
    if (linenb < 2)
    {
        if (setSize(level, line))
            ++gap;
    }
    if (linenb >= level.content().size()+gap)
    {
        if (line.substr(0, nbOfRandomWalls.size()) == nbOfRandomWalls)
            changeNbOfRandomWalls(level, line.substr(nbOfRandomWalls.size(),
                                                     line.size()));
        else if (line.substr(0, nbOfCats.size()) == nbOfCats)
            changeNbOfCats(level, line.substr(nbOfCats.size(), line.size()));
        return true;
    }
    sf::Vector2i pos(0, 0);
    for (unsigned int i = 0; i < line.size(); i++)
    {
        if (!old)
            pos.x = i, pos.y = linenb-gap;
        else
            pos.x = linenb-gap, pos.y = i;
        if (line[i] == CHAR_MOUSE)
            level.setMouseStartPos(pos);
        level.setCaseType(pos, line[i]);
    }
    if (linenb == gv.LVL_Y+gap-1)
        gap = 0;
    return true;
}

bool LevelFileInterpreter::setSize(Level &level, const string &line)
{
    unsigned int size = 0;
    if (line.substr(0, levelSizeX.size()) == levelSizeX)
    {
        size = gv.textToNb(line.substr(levelSizeX.size(), line.size()));
        if (size > 0)
            gv.LVL_X = size;
    }
    else if (line.substr(0, levelSizeY.size()) == levelSizeY)
    {
        size = gv.textToNb(line.substr(levelSizeY.size(), line.size()));
        if (size > 0)
            gv.LVL_Y = size;
    }
    if (size > 0)
    {
        gv.resizeGame();
        level.resizeLevel();
        return true;
    }
    return false;
}

void LevelFileInterpreter::changeNbOfCats(Level &level, const string &nb)
{
    unsigned int number = 0;
    istringstream oss(nb);
    oss >> number;
    if (number < 0 || number > level.nbOfCasetype(NOTHING))
        return;
    level.setNbOfCats(number);
    cout << "Number of cats set to " << number << " for this level.\n";
}

void LevelFileInterpreter::changeNbOfRandomWalls(Level &level, const string &nb)
{
    unsigned int number = 0;
    istringstream oss(nb);
    oss >> number;
    if (number < 0 || number > gv.LVL_X*gv.LVL_Y)
        return;
    level.setNbOfRandomWalls(number);
    cout << "Number of random walls set to " << number << " for this level.\n";
}

char LevelFileInterpreter::casetypeToChar(const CASETYPE &casetype)
{
    char character = CHAR_NOTHING;
    if (casetype == BLOCK)
        character = CHAR_BLOCK;
    else if (casetype == WALL)
        character = CHAR_WALL;
    else if (casetype == STAIRS)
        character = CHAR_STAIRS;
    return character;
}
