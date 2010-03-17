#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>
#include <SFML/Graphics.hpp>

const unsigned int DLVL_X =  23;
const unsigned int DLVL_Y = 23;
const unsigned int CASE_SIZE = 16;
const unsigned int HUD_HEIGHT = 35;
const unsigned int DSCREEN_W = DLVL_X * CASE_SIZE;
const unsigned int DSCREEN_H = DLVL_Y * CASE_SIZE + HUD_HEIGHT;
const float CAT_SPEED = 0.75f;
const unsigned int SCORE_BY_CAT = 10;
const unsigned int DEFAULTNB_OF_CAT = 3;
const std::string defaultTheme = "data/default/";

struct GameVariables
 {
     GameVariables();

    bool debugMode, sizeChanged;
    unsigned int LVL_X, LVL_Y, SCREEN_W, SCREEN_H;
    unsigned int nbOfCats, catsCannotMoveNbBeforeDead, score;
    std::string currentTheme;

    void resizeGame();
    static void drawFps(sf::RenderWindow &App);
    static int textToNb(const std::string &text);
    static std::string nbToText(const int &nb);
 };

 extern GameVariables gv;

#endif /* CONSTANTES_HPP */
