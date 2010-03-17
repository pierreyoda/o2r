#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "gui/HudManager.hpp"
#include "Game.hpp"

class Engine
{
    public:
        Engine(sf::RenderWindow &window, const bool &vsync = true,
               const unsigned int &fpslimit = 60);
        ~Engine();

        void run();

    private:
        inline bool loadLevel(const std::string &filename);
        inline bool loadTower(const std::string &filename);
        void runGame();
            inline void initializeGame(const bool &newlvl = true);
            bool menuGame();
            void resizeGameView();
        void runEditor();
            bool menuEditor();
        inline void drawFps();

        sf::RenderWindow &App;
        Game game;
        l_cats &cats;
        Mouse &mouse;
        HudManager hud;
        sf::View gameView;
        int gameViewZoomFactor;
};

#endif /* ENGINE_HPP */
