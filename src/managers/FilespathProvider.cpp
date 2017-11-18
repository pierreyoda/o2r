#include <QMap>
#include "FilespathProvider.hpp"
#include "QsLog.h"

typedef QListIterator<QFileInfo> QFileInfoListIterator;
typedef QMapIterator<QString, QString> AssetsMapIterator;

namespace FilespathProvider {

namespace {
    QDir MAIN_MOD_PATH("");
    QDir MODS_LOCATION("");
    QStringList MODS_LIST;
    QStringList ASSETS_NAME_FILTERS("*");
    QMap<QString, QString> ASSETS_MAP;
} // anonymous namespace

QString assetPathFromAlias(const QString &alias)
{
    return ASSETS_MAP.value(alias, "");
}

/** \internal Refresh the assets list from the given dir.
*@param dir Directory where to search.
*/
void refreshAssetsListFromDir(const QDir &dir)
{
    dir.refresh();
    // Get the files list, accorting to the filters and sorted by name
    QFileInfoList filesList = dir.entryInfoList(ASSETS_NAME_FILTERS,
                                                QDir::Files, QDir::Name);
    // Update the assets list
    QFileInfoListIterator fileInfoIter(filesList);
    while (fileInfoIter.hasNext())
    {
        QFileInfo fileInfo = fileInfoIter.next();
        ASSETS_MAP[fileInfo.fileName()] = fileInfo.filePath();
    }
}

void refreshAssetsList()
{
    // Clear current list
    ASSETS_MAP.clear();

    // First search in main mod
    refreshAssetsListFromDir(MAIN_MOD_PATH);
    // Then search in other mods, overwriting if needed
    QStringListIterator modIter(MODS_LIST);
    while (modIter.hasNext())
    {
        QDir modPath(MODS_LOCATION);
        modPath.cd(modIter.next());
        refreshAssetsListFromDir(modPath);
    }

    // Finally, log the new assets list
    QString log("FilespathProvider : refreshed assets list :");
    AssetsMapIterator assetIter(ASSETS_MAP);
    while (assetIter.hasNext())
    {
        assetIter.next();
        log += QString("\n\t-asset name = \"%1\" \t\t path=\"%2\"")
                .arg(assetIter.key(), assetIter.value());
    }
    log += ".";
    QLOG_INFO() << log.toLocal8Bit().constData(); // avoids quotation marks
}

QString mainModPath()
{
    return MAIN_MOD_PATH.path();
}

void setMainModFolder(const QString &folder)
{
    if (isModValid(folder, true))
    {
        MAIN_MOD_PATH = MODS_LOCATION;
        MAIN_MOD_PATH.cd(folder);
        QLOG_INFO() << "FilespathProvider : main mod set to"
                    << MAIN_MOD_PATH.path() << ".";
    }
    else
    {
        QLOG_ERROR() << "FilespathProvider : cannot set main mod to"
                     << folder
                     << ": invalid mod.";
    }
}

const QStringList &modsList()
{
    return MODS_LIST;
}

void addMods(const QStringList &mods, bool resetModsList)
{
    // Reset current mods list if requested
    if (resetModsList)
        MODS_LIST.clear();
    // Add all valid mods
    QStringListIterator modIter(mods);
    while (modIter.hasNext())
    {
        QString modName = modIter.next();
        if (isModValid(modName))
            MODS_LIST.append(modName);
        else
            QLOG_WARN() << "FilespathProvider : cannot add mod"
                        << modName
                        << ": invalid mod.";
    }
    // Log the new mods list
    QString log("FilespathProvider : new mods list is ");
    if (!MODS_LIST.empty())
    {
        modIter = MODS_LIST;
        log += ":";
        while (modIter.hasNext())
            log += QString("\n\t-mod name = \"%1\"").arg(modIter.next());
    }
    else
        log += "empty.";
    QLOG_INFO() << log.toLocal8Bit().constData()
                << "\n\tIn mods location:" << MODS_LOCATION.path();
}

bool isModValid(const QString &path, bool isMainMod)
{
    // Is the mods location defined and existing?
    if (!MODS_LOCATION.exists())
    {
        QLOG_ERROR() << "FilespathProvider : undefined mods location.";
        return false;
    }
    if (path.isEmpty())
        return false;
    QDir temp(MODS_LOCATION);
    // Is the provided path a folder in the mods location folder?
    if (!temp.cd(path))
        return false;
    // Is the provided path different from the main mod path?
    return (isMainMod || temp != MAIN_MOD_PATH);
}

QString modsLocation()
{
    return MODS_LOCATION.path();
}

void setModsLocation(const QString &path)
{
    QDir temp(path);
    if (temp.exists() && temp.isReadable())
    {
        MODS_LOCATION = temp;
        QLOG_INFO() << "FilespathProvider : mods location set to"
                  << MODS_LOCATION.path();
    }
    else
    {
        QLOG_ERROR() << "FilespathProvider : cannot set mods location to"
                     << temp.path()
                     << ": invalid path";
    }
}

void setAssetsNameFilters(const QStringList &nameFilters)
{
    ASSETS_NAME_FILTERS = nameFilters;
}

} // namespace FilespathProvider
