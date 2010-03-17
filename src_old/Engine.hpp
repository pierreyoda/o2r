#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Mouse.hpp"
#include "Cat.hpp"

class Engine
{
    public:
        Engine(sf::RenderWindow &window, const bool &vsync = true,
               const unsigned int &fpslimit = 60);
        ~Engine();

        void run();

    private:
        void zoom(const bool &in);
            void returnToNormalZoom();
        bool loadLevel(const std::string &filename);
        void runGame();
            void initializeGame(const bool &newlvl = false);
            bool menuGame();
            void resizeGameView();
        void runEditor();
            bool menuEditor();
            void clearCase(const sf::Vector2f &mousepos);
            void placeCaseType(const sf::Vector2f &mousepos, const CASETYPE &type);
            void placeMouse(const sf::Vector2f &mousepos);
        void drawHud(const bool &ingame = false, const bool &ineditor = false);
            void initializeHud();
            void drawEditorHud();
        sf::Vector2i pixelToCase(const sf::Vector2f &pos);

        sf::RenderWindow &App;
        Level level;
        std::vector <Cat> cats;
        Mouse mouse;
        sf::String sScore, sNbOfCats, sEditorBlock, sEditorWall, sEditorMouse;
        sf::Sprite editorBlock, editorWall, editorMouse;
        sf::Shape hudBackground;
        std::string currentLevel;
        sf::View gameView;
        int gameViewZoomFactor;
};

#endif /* ENGINE_HPP */
