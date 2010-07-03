#ifndef LAUNCHEREDITIONENGINE_HPP
#define LAUNCHEREDITIONENGINE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "gui/HudManager.hpp"
#include "GlobalVariables.hpp"
#include "Game.hpp"

class LauncherEditionEngine
{
    public:
        LauncherEditionEngine(sf::RenderWindow &window,
            const bool &vsync = true, const unsigned int &fpslimit = 60,
            const bool &adjustWindowSize = false);
        ~LauncherEditionEngine();

        void runAsGame(const std::string &level,
                        const int &nbOfCats, const int &nbOfRW,
                        const bool &towerMode = false);
        void runAsEditor(const std::string &level,
                        const bool &emptyLevel,
                        const sf::Vector2i &sizeIfEmpty,
                        const int &nbOfCats, const int &nbOfRW,
                        const bool &noWarningAtSave);

    private:
        void resetView();
        void ajustWindowToLevelSize();
        void drawFps();
        void editorSaveLevelBeforeExit(const std::string &level,
                                       const bool &noWarningAtSave);

        sf::RenderWindow &App;
        sf::View gameView;
        Game game;
        l_cats &cats;
        Mouse &mouse;
        HudManager hud;
        const bool adjustWindowSize;
};

#endif /* LAUNCHEREDITIONENGINE_HPP */
