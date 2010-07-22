#ifndef GLOBALVARIABLES_HPP
#define GLOBALVARIABLES_HPP

#include <list>
#include <string>
#include <sstream>
#include "constantes.hpp"

struct LesElement
{
    LesElement() : character(CHAR_NOTHING),  type(NOTHING),
        imagefile("nothing.png")
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

    bool debugMode, sizeChanged, compatibilityMode, useShaders;
    unsigned int score, mouseNbOfLives;
    const unsigned int catsCannotMoveNbBeforeDead;
    std::string windowTitle;
    l_LesElement baseLesElements, lesElements;

    void resizeGame();

    int textToNb(const std::string &text)
    {
        std::istringstream iss(text);
        int nb;
        iss >> nb;
        return nb;
    }
    template <typename T> std::string nbToText(const T &nb)
    {
        std::ostringstream oss;
        oss << nb;
        return oss.str();
    }
};

 extern GlobalVariables gv;

#endif /* GLOBALVARIABLES_HPP */
