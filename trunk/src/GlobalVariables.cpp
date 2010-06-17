#include "GlobalVariables.hpp"

GlobalVariables gv;

GlobalVariables::GlobalVariables() : debugMode(false), sizeChanged(false),
    score(0), catsCannotMoveNbBeforeDead(NBOF_CATS_CANNOT_MOVE_BEFORE_DEAD),
    windowTitle("Open Rodent's Revenge v." + gameVersion)
{
    baseLesElements.push_back(LesElement(CHAR_NOTHING, NOTHING, "void.png"));
    baseLesElements.push_back(LesElement(CHAR_BLOCK, BLOCK, "block.png"));
    baseLesElements.push_back(LesElement(CHAR_WALL, WALL, "wall.png"));
    baseLesElements.push_back(LesElement(CHAR_STAIRS, STAIRS, "stairs.png"));
}

GlobalVariables::~GlobalVariables()
{

}

void GlobalVariables::resizeGame()
{
    sizeChanged = true;
}
