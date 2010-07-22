#include "GlobalVariables.hpp"
#include "tools/FilesPathHandler.hpp"

GlobalVariables gv;
FilesPathHandler gFph;

GlobalVariables::GlobalVariables() : debugMode(false), sizeChanged(false),
    compatibilityMode(false), useShaders(!compatibilityMode), score(0),
    mouseNbOfLives(DEFAULTNB_OF_CAT),
    catsCannotMoveNbBeforeDead(NBOF_CATS_CANNOT_MOVE_BEFORE_DEAD),
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
