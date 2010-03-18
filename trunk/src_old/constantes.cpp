#include <sstream>
#include "constantes.hpp"

GameVariables gv;

using namespace sf;

GameVariables::GameVariables() : debugMode(false), sizeChanged(false),
    nbOfCats(3), catsCannotMoveNbBeforeDead(DEFAULTNB_OF_CAT), score(0),
    currentTheme(defaultTheme)
{
    LVL_X = DLVL_X, LVL_Y = DLVL_Y, SCREEN_W = DSCREEN_W, SCREEN_H = DSCREEN_H;
}

void GameVariables::resizeGame()
{
    sizeChanged = true;
    SCREEN_W = LVL_X * CASE_SIZE, SCREEN_H = LVL_Y * CASE_SIZE + HUD_HEIGHT;
}

void GameVariables::drawFps(RenderWindow &App)
{
    static bool init = false;
    static Clock refreshClock;
    static String string;
    if (!init || refreshClock.GetElapsedTime() >= 1.f)
    {
        float fps = 1.f / App.GetFrameTime();
        if (fps < 0)
            fps = 0;
        string.SetText(nbToText(static_cast<int>(fps)));
        if (!init)
            init = true;
        refreshClock.Reset();
    }
    App.Draw(string);
}

std::string GameVariables::nbToText(const int &nb)
{
    std::ostringstream oss;
        oss << nb;
    return oss.str();
}

int GameVariables::textToNb(const std::string &text)
{
    int nb = 0;
    std::istringstream iss(text);
        iss >> nb;
    return nb;
}
