#ifndef TOWERFILEINTERPRETER_HPP
#define TOWERFILEINTERPRETER_HPP

#include <string>
#include <tinyxml.h>
#include "Tower.hpp"

class TowerFileInterpreter
{
    public:
        static bool readTower(Tower &tower, const std::string &filename);

        static bool readLes(const std::string &filename, l_LesElement &lesElements,
                            const bool &clearPreviousLes = true);

    private:
        static bool readStairs(TiXmlElement *elem, Tower &tower);
            static bool readStairs(const std::string &filename, Tower &tower);
        static bool readLes(TiXmlElement *elem, l_LesElement &lesElements);
};

#endif /* TOWERFILEINTERPRETER_HPP */
