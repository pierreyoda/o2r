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
        Game(const bool &loadDefaultLevel = true);
        ~Game();

        void testTower();

        void renderTower(sf::RenderTarget &target);
        void update(const bool &astar);
        bool loadTower(const std::string &filename);
        bool saveLevel(const std::string &filename);
        bool loadLevel(const std::string &filename,
                const sf::Vector2i &sizeIfEmpty = sf::Vector2i(DLVL_X, DLVL_Y),
                const int persoNbOfCats = -1, const int persoNbOfRW = -1,
                const bool &initGame = true);
            void initializeGame(const bool &newlvl = false);
        void clearCase(const sf::Vector2f &mousepos);
        void placeCaseType(const sf::Vector2f &mousepos, const CASETYPE &type);
        void placeMouse(const sf::Vector2f &mousepos);

        Level &getLevel() { return *currentLevel.get(); }
        l_cats &getCatsList() { return cats; }
        Mouse &getMouse() { return mouse; }
        std::string getCurrentLevelName() const { return currentLevel->getInfos().filename; }

    private:
        void updateLevelPointersFromTower();
        void initializeLevel();
        inline sf::Vector2i pixelToCase(const sf::Vector2f &pos) const;
        void mouseOnStairs();
        void updateCats(const bool &astar);

        levelPtr currentLevel;
        boost::shared_ptr<Tower> tower;
        l_cats cats;
        Mouse mouse;
        bool inTower;
};

#endif /* GAME_HPP */
