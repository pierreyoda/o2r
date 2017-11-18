#ifndef TILEDMAPFACTORY_HPP
#define TILEDMAPFACTORY_HPP

#include <QPair>
#include <QFile>

class TiledMap;

typedef QPair<QString, QString> Option;

/** Static class able to load/save a TiledMap.
*
*XML manipulation is realized with QtXML in DOM, with the help of
*<a href=http://techbase.kde.org/Development/Tutorials/QtDOM_Tutorial>this tutorial</a>.
*
* @see TiledMap
*/
struct TiledMapFactory
{
    static unsigned int computeLevelSizeX(const TiledMap &level);

    static TiledMap *loadLevel(const QString &path);

    static bool saveLevel(TiledMap &level, const QString &path);

private:
    // Load
    static void loadMapTxtFormat(TiledMap &level, QFile &file);
    static Option processTxtOptionLine(const QString &line);

    static void loadMapXmlFormat(TiledMap &level, QFile &file);

    static bool interpretOption(const Option &option, TiledMap &lvl, bool oldFormat);
    static bool processTilesLine(const QString &line, TiledMap &lvl, unsigned int lineNb,
                                 bool oldFormat);

    // Save
    static bool saveMapTxtFormat(const TiledMap &level);
    static QString formTxtOptionLine(const QString &name, const QString &value);

    static bool saveMapXmlFormat(const TiledMap &level);
};

#endif // TILEDMAPFACTORY_HPP
