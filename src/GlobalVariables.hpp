#ifndef GLOBALVARIABLES_HPP
#define GLOBALVARIABLES_HPP

#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "constantes.hpp"

struct LesElement
{
    LesElement() : character('0'),  type(NOTHING), imagefile("nothing.png")
    { }
    LesElement(const char &letter, const CASETYPE &ctype, const std::string &imgfile) :
        character(letter), type(ctype), imagefile(imgfile)
    { }

    char character;
    CASETYPE type;
    std::string imagefile;
};

typedef std::list<LesElement> l_LesElement;

struct GlobalVariables
{
    GlobalVariables();
    ~GlobalVariables();

    bool debugMode, sizeChanged;
    unsigned int LVL_X, LVL_Y, SCREEN_W, SCREEN_H;
    unsigned int score;
    const unsigned int catsCannotMoveNbBeforeDead;
    std::string windowTitle;
    l_LesElement baseLesElements, lesElements;

    void resizeGame();
    static void drawFps(sf::RenderWindow &App);
    static int textToNb(const std::string &text);
    static std::string nbToText(const int &nb);
};

 extern GlobalVariables gv;

#endif /* GLOBALVARIABLES_HPP */
