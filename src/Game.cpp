#include <iostream>
#include "Game.hpp"
#include "TowerFileInterpreter.hpp"
#include "tools/FilesLoader.hpp"
#include "tools/Logger.hpp"

using namespace sf;

// TODO (Pierre-Yves#1#): [TOWER] 0.8 : Charger et afficher les Tower
// TODO (Pierre-Yves#1#): [TOWER] Ajouter 'initializeFloor' (--> facile : initializeGame() avec nb chats perso et reset(floor) du pointeur) à Game
Game::Game(const bool &loadDefaultLevel) : cats(), mouse(currentLevel, cats), inTower(false)
{
    if (loadDefaultLevel)
        loadLevel("data/1.txt");
    //loadLevel("data/logobig.txt");
}

Game::~Game()
{
    if (tower.unique())
        tower.reset();
    if (currentLevel.unique())
        currentLevel.reset();
}

void Game::testTower()
{
    loadTower("data/towertest/testtower.xml");
    updateLevelPointersFromTower();
}

void Game::updateLevelPointersFromTower()
{
    if (tower == 0)
        return;
    currentLevel = tower->getCurrentFloor();
    mouse.updateLevelPtr(currentLevel);
}

void Game::renderTower(RenderTarget &target)
{
    if (currentLevel.get() == 0)
        return;
    if (inTower && tower != 0)
        tower->render(target);
    else if (gv.compatibilityMode)
        currentLevel->renderToOtherTarget(target);
    else
        target.Draw(currentLevel->getRenderResult());
}

bool Game::loadTower(const std::string &filename)
{
    if (filename.empty())
        return false;
    //gv.lesElements.clear();
    tower.reset(new Tower(filename));
    if (tower == 0 || tower->getCurrentFloor() == 0)
        return false;
    inTower = true;
    updateLevelPointersFromTower();
    return true;
}

bool Game::saveLevel(const std::string &filename)
{
    return currentLevel->writeLevel(filename);
}

bool Game::loadLevel(const std::string &filename, const Vector2i &sizeIfEmpty,
    const int persoNbOfCats, const int persoNbOfRW, const bool &initGame)
{
    if (filename.empty() || (filename != emptyLevelName &&
                             !FilesLoader::fileExists(filename)))
        return false;
    currentLevel.reset(new Level(filename, "", sizeIfEmpty, persoNbOfCats,
                                 persoNbOfRW));
    mouse.updateLevelPtr(currentLevel);
    inTower = false;
    if (initGame)
        initializeGame(true);
    return true;
}

void Game::initializeGame(const bool &newlvl)
{
    gLog << "Initializing game.\n";
    gv.score = 0;
    mouse.revive();
    cats.clear();
    if (!newlvl && loadLevel("data/1.txt"))
        return;
    initializeLevel();
}

void Game::initializeLevel()
{
    currentLevel->randomWalls();
    mouse.setPosition(currentLevel->getInfos().mouseStartPos);
    for (unsigned int i = 0; i < currentLevel->getInfos().catsNb; i++)
    {
        Cat cat;
        cat.placeCat(*currentLevel.get(), cats);
        cats.push_back(cat);
    }
}

void Game::mouseOnStairs()
{
    if (currentLevel->getCaseType(mouse.pos()) != STAIRS)
        return;
}

void Game::updateCats(const bool &astar)
{
    static l_cats::iterator iter;
    for (iter = cats.begin(); iter != cats.end(); iter++)
    {
        Cat &cat = *iter;
        if (cat.isAlive())
        {
            if (cat.moveCat(*currentLevel.get(), mouse.pos(), cats, astar) &&
                    !mouse.dead())
                mouse.die();
            if (cat.cannotMoveNb() > 0)
                cat.setImage(gImageManager.getResource("cat_awaiting.png"));
            else
                cat.setImage(gImageManager.getResource("cat.png"));
            if (cat.cannotMoveNb() >= gv.catsCannotMoveNbBeforeDead)
            {
                cat.die();
                --currentLevel->getInfosRef().catsNb;
            }
        }
    }
}

void Game::clearCase(const Vector2f &mousepos)
{
    currentLevel->setCaseType(pixelToCase(mousepos), NOTHING);
}

void Game::placeCaseType(const Vector2f &mousepos, const CASETYPE &type)
{
    Vector2i pos = pixelToCase(mousepos);
    if (pos != currentLevel->getInfos().mouseStartPos)
        currentLevel->setCaseType(pos, type);
}

void Game::placeMouse(const Vector2f &mousepos)
{
    Vector2i pos = pixelToCase(mousepos);
    if (!Object::outOfScreen(pos, currentLevel->getInfos().size))
    {
        currentLevel->setCaseType(pos, NOTHING);
        currentLevel->setMouseStartPos(pos);
        mouse.setPosition(pos);
    }
}

Vector2i Game::pixelToCase(const Vector2f &pos) const
{
    unsigned int x = static_cast<unsigned int>(pos.x/CASE_SIZE),
        y = static_cast<unsigned int>(pos.y/CASE_SIZE);
    return Vector2i(x, y);
}
