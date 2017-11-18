#include "LevelInfo.hpp"

LevelInfo::LevelInfo() : name(), author(),
    date(QDate::currentDate()), filePath(), lesFilePath(), mousePosX(0),
    mousePosY(0), mouseRandomPos(false)
{
}
