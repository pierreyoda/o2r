#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#include <SFML/Graphics.hpp>

class HudManager
{
    public:
        HudManager();

        void createHud();
        void newGameStarted();

        const sf::Sprite &drawHud(const unsigned int &catsNb,
            const unsigned int &remainingLifesNb, const bool &inGame = true);
        static void drawFps(sf::RenderTarget &target, const float &fpsCount);

    private:
        bool updateScore();
        bool updateNbOfCats(const unsigned int &catsNb);
        bool updateNbOfRemainingLifes(const unsigned int &lifesNb);

        sf::RenderImage renderTarget, remainingLifesTarget;
        sf::Sprite renderResult, remainingLifes;
        sf::Text score, nbOfCats, editorBlock, editorWall, editorMouse;
        sf::Sprite sEditorBlock, sEditorWall, sEditorMouse;
        sf::Shape hudBackground;
        bool m_gamestart;
};

#endif /* HUDMANAGER_HPP */
