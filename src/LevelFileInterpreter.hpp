#ifndef LEVELFILEINTERPRETER_HPP
#define LEVELFILEINTERPRETER_HPP

#include <string>
#include "Level.hpp"

class LevelFileInterpreter
{
    public:
        static bool writeLevel(Level &level, const std::string &filename,
                               const bool &oldmethod = false);
        static bool readLevel(Level &level, const std::string &filename);

    private:
        static bool setSize(Level &level, const std::string &line);
        static void changeNbOfCats(Level &level, const std::string &nb);
        static void changeNbOfRandomWalls(Level &level, const std::string &nb);
        static char casetypeToChar(const CASETYPE &casetype);
        static bool analyseLine(Level &level, const std::string &line,
                            const unsigned int &linenb, const bool &old = false);
};

#endif /* LEVELFILEINTERPRETER_HPP */
