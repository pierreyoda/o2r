#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "../GlobalVariables.hpp"

class HudManager
{
    public:
        HudManager(sf::RenderTarget *otherTarget = 0);
        ~HudManager();

        void createHud(const sf::Vector2i &levelSize,
                       const bool &useOtherTarget = gv.compatibilityMode);
        void newGameStarted();

        const sf::Sprite &drawHud(const unsigned int &catsNb,
            const unsigned int &remainingLifesNb, const bool &inGame);
        void renderToOtherTarget(const unsigned int &catsNb,
            const unsigned int &remainingLifesNb, const bool &inGame);
        static void drawFps(sf::RenderTarget &target, const float &fpsCount,
                const sf::Vector2i &screenSize = sf::Vector2i(SCREEN_W, SCREEN_H));

    private:
        bool updateScore();
        bool updateNbOfCats(const unsigned int &catsNb);
        bool updateNbOfRemainingLifes(const unsigned int &lifesNb);

        sf::RenderTarget *otherTarget;
        sf::RenderImage renderTarget, remainingLifesTarget;
        sf::Sprite renderResult, remainingLifes;
        sf::Text score, nbOfCats, editorBlock, editorWall, editorMouse;
        sf::Sprite sEditorBlock, sEditorWall, sEditorMouse;
        sf::Shape background;
        bool m_gamestart;
};

#endif /* HUDMANAGER_HPP */
