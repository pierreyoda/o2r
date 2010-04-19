#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "gui/Menu.hpp"
#include "Game.hpp"

class Engine
{
    public:
        Engine(sf::RenderWindow &window, const bool &vsync = true,
               const unsigned int &fpslimit = 60);
        ~Engine();

        void run();

    private:
        void createMenus();
        inline bool loadLevel(const std::string &filename);
        inline bool loadTower(const std::string &filename);
        void runGame();
            inline void initializeGame(const bool &newlvl = true);
            bool menuGame();
            void resizeGameView(const sf::Vector2i &prevSize);
        void runEditor();
            bool menuEditor();
                void buttonSave();
                void buttonLoad();
        inline void drawFps();
        inline void closeMenu() { resume = true; }
        inline void toMainMenu() { quitToMainMenu = true; }
        inline void exit() { running = false; }

        sf::RenderWindow &App;
        Game game;
        l_cats &cats;
        Mouse &mouse;
        HudManager hud;
        Menu mainMenu, gameMenu, editorMenu;
        sf::View gameView;
        int gameViewZoomFactor;
        bool running, resume, quitToMainMenu;
};

#endif /* ENGINE_HPP */
