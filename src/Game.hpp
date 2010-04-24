#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "Tower.hpp"
#include "Mouse.hpp"
#include "Cat.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void testTower();

        void renderTower(sf::RenderTarget &target);
        void update();
        bool loadTower(const std::string &filename);
        bool loadLevel(const std::string &filename);
            void initializeGame(const bool &newlvl = false);
        void updateCats(const bool &astar);
        void clearCase(const sf::Vector2f &mousepos);
        void placeCaseType(const sf::Vector2f &mousepos, const CASETYPE &type);
        void placeMouse(const sf::Vector2f &mousepos);
        void setCurrentLevelName(const std::string &newlevel)
        {
            currentLevel->setFilename(newlevel);
        }

        Level &getLevel() { return *currentLevel.get(); }
        l_cats &getCatsList() { return cats; }
        Mouse &getMouse() { return mouse; }
        std::string getCurrentLevelName() const { return currentLevel->getFilename(); }

    private:
        void updateLevelPointersFromTower();
        void initializeLevel();
        inline sf::Vector2i pixelToCase(const sf::Vector2f &pos) const;
        inline void resetLevel();
        void mouseOnStairs();

        levelPtr currentLevel;
        Tower *tower;
        l_cats cats;
        Mouse mouse;
        bool inTower;
};

#endif /* GAME_HPP */
