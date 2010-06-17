#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>

#ifndef USE_GUIFRAMEWORK
#define USE_GUIFRAMEWORK 0
#endif /* USE_GUIFRAMEWORK */

const unsigned int DLVL_X =  23;
const unsigned int DLVL_Y = 23;
const unsigned int CASE_SIZE = 16;
const unsigned int HUD_HEIGHT = 35;
const unsigned int SCREEN_W = DLVL_X * CASE_SIZE;
const unsigned int SCREEN_H = DLVL_Y * CASE_SIZE + HUD_HEIGHT;
const unsigned int SCORE_BY_CAT = 10;
const unsigned int DEFAULTNB_OF_CAT = 3;
const unsigned int NBOF_CATS_CANNOT_MOVE_BEFORE_DEAD = 3;
const unsigned int DEFAULT_RESPAWN_SECURITYLVL = 30;
const unsigned int HUD_SPACE_BETWEEN_LIFES = 5;
const unsigned int DEFAULT_NB_OF_LIFES = 3;
const float CAT_SPEED = 0.75f;
const bool ORIGIN_AT_CENTER = false;
const bool USE_WINDOWGUI = USE_GUIFRAMEWORK;
const float BUTTON_DEFAULT_BORDER = 8.f;
const char stairsDescriptionDefaultFlag = ':';
const std::string baseModule = "data/base/";
const std::string gameVersion = "0.6";
const std::string emptyLevelName = "*empty*";

enum CASETYPE
{
    UNDEFINED,
    NOTHING,
    BLOCK,
    WALL,
    STAIRS
};
const char CHAR_NOTHING = '0';
const char CHAR_BLOCK = '1';
const char CHAR_WALL = '2';
const char CHAR_MOUSE = 'M';
const char CHAR_STAIRS = 'S';

#endif /* CONSTANTES_HPP */
