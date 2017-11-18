#ifndef LEVELINFO_HPP
#define LEVELINFO_HPP

#include <QDate>
#include <QFileInfo>

/** LevelInfo contains all the informations needed in order to form a complete level.
*Contains : name, author, creation date, (optional) external LES file,
*and mouse start position informations.
*Each TiledMap has its own LevelInfo.
*/
class LevelInfo
{
public:
    LevelInfo();

    QString name;
    QString author;
    QDate date;
    QString filePath;
    QString lesFilePath;
    unsigned int mousePosX, mousePosY;
    bool mouseRandomPos;
};

#endif // LEVELINFO_HPP
