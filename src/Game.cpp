#include <iostream>
#include "Game.hpp"
#include "LevelFileInterpreter.hpp"
#include "TowerFileInterpreter.hpp"

using namespace sf;

// TODO (Pierre-Yves#1#): [TOWER] Ajouter 'initializeFloor' (--> facile : initializeGame() avec nb chats perso et reset(floor) du pointeur) � Game avec nbChats/niveau au niveau de Tower
Game::Game() : currentLevel(new Level()), tower(new Tower()), cats(), mouse(currentLevel, cats),
    inTower(false)
{

}

Game::~Game()
{
    cats.clear();
    delete tower; //Crash (when loading tower)!
}

void Game::testTower()
{
    /*loadTower("data/towertest/testtower.xml");
    //tower->setCurrentFloor(1);
    updateLevelPointersFromTower();*/
    loadLevel("data/logobig.txt");
}

void Game::updateLevelPointersFromTower()
{
    if (tower->getCurrentFloor() == NULL)
        return;
    currentLevel.reset(tower->getCurrentFloor());
    mouse.updateLevelPtr(currentLevel);
}

void Game::renderTower(RenderTarget &target)
{
    if (currentLevel.get() == NULL)
        return;
    if (inTower)
        tower->render(target);
    else
        target.Draw(currentLevel->getRenderResult());
}

bool Game::loadTower(const std::string &filename)
{
    if (filename == "")
        return false;
    gv.lesElements.clear();
    if (!TowerFileInterpreter::readTower(*tower, filename))
    {
        resetLevel();
        return false;
    }
    inTower = true;
    currentLevel.reset(tower->getCurrentFloor());
    mouse.updateLevelPtr(currentLevel);
    return true;
}

bool Game::loadLevel(const std::string &filename)
{
    if (filename == "")
        return false;
    gv.lesElements.clear();
    currentLevel.reset(new Level(true));
    if (!LevelFileInterpreter::readLevel(*currentLevel.get(), filename))
    {
        resetLevel();
        return false;
    }
    currentLevel->setFilename(filename);
    mouse.updateLevelPtr(currentLevel);
    inTower = false;
    initializeGame(true);
    return true;
}

void Game::initializeGame(const bool &newlvl)
{
    std::cout << "Initializing game.\n";
    gv.score = 0;
    mouse.revive();
    cats.clear();
    if (!newlvl && loadLevel("data/1.txt"))
        return;
    initializeLevel();
    std::vector< std::vector<LevelCase> >  a = currentLevel->content();
    std::cout << a.size() << "\n";
}

void Game::initializeLevel()
{
    currentLevel->randomWalls();
    mouse.setPosition(currentLevel->getMouseStartPos());
    for (unsigned int i = 0; i < currentLevel->getCatsNb(); i++)
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
    for (unsigned int i = 0; i < cats.size(); i++)
    {
        Cat &cat = cats[i];
        if (cat.isAlive())
        {
            if (cat.moveCat(*currentLevel.get(), mouse.pos(), cats, astar) && !mouse.dead())
                mouse.die();
            if (cat.cannotMoveNb() > 0)
                cat.setImage(*gImageManager.getResource("cat_awaiting.png"));
            else
                cat.setImage(*gImageManager.getResource("cat.png"));
            if (cat.cannotMoveNb() >= gv.catsCannotMoveNbBeforeDead)
                cat.die();
        }
    }
}

void Game::resetLevel()
{
    currentLevel.reset(new Level());
}

void Game::clearCase(const Vector2f &mousepos)
{
    currentLevel->setCaseType(pixelToCase(mousepos), NOTHING);
}

void Game::placeCaseType(const Vector2f &mousepos, const CASETYPE &type)
{
    Vector2i pos = pixelToCase(mousepos);
    if (pos != currentLevel->getMouseStartPos())
        currentLevel->setCaseType(pos, type);
}

void Game::placeMouse(const Vector2f &mousepos)
{
    Vector2i pos = pixelToCase(mousepos);
    currentLevel->setCaseType(pos, NOTHING);
    currentLevel->setMouseStartPos(pos);
    mouse.setPosition(pos);
}

Vector2i Game::pixelToCase(const Vector2f &pos) const
{
    unsigned int x = static_cast<unsigned int>(pos.x/CASE_SIZE),
        y = static_cast<unsigned int>(pos.y/CASE_SIZE);
    return Vector2i(x, y);
}
