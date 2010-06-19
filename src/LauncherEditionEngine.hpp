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
            const bool &vsync = true, const unsigned int &fpslimit = 60);
        ~LauncherEditionEngine();

        void runAsGame(const std::string &level,
                        const int &nbOfCats,
                        const int &nbOfRW);
        void runAsEditor(const std::string &level,
                        const sf::Vector2i &sizeIfEmpty,
                        const bool &noWarningAtSave = true);

    private:
        void resetView();

        sf::RenderWindow &App;
        sf::View gameView;
        Game game;
        l_cats &cats;
        Mouse &mouse;
        HudManager hud;
};

#endif /* LAUNCHEREDITIONENGINE_HPP */