/*
    Open Rodent's Revenge is the open-source remake of Microsoft's game "Rodent's Revenge" (1991).
    Copyright (C) 2010-2012  Pierre-Yves Diallo (Pierreyoda).
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

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
QMap<QString, QString> ASSETS_LIST;
} // anonymous namespace

/** \internal Refresh the assets list from the given dir.
*/
void refreshAssetsListFromDir(const QDir &dir);

void refreshAssetsList()
{
    // Clear current list
    ASSETS_LIST.clear();

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
    AssetsMapIterator assetIter(ASSETS_LIST);
    while (assetIter.hasNext())
    {
        assetIter.next();
        log += QString("\n\t-asset name = \"%1\" \t\t path=\"%2\"")
                .arg(assetIter.key(), assetIter.value());
    }
    log += ".";
    QLOG_INFO() << log.toLocal8Bit().constData(); // avoids quotation marks
}

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
        ASSETS_LIST[fileInfo.baseName()] = fileInfo.filePath();
    }
}

QString mainModPath()
{
    return MAIN_MOD_PATH.path();
}

void setMainModFolder(const QString &folder)
{
    if (isModValid(folder))
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

bool isModValid(const QString &path)
{
    // Is the mods location defined and existing?
    if (!MODS_LOCATION.exists())
    {
        QLOG_ERROR() << "FilespathProvider : undefined mods location.";
        return false;
    }
    // Is the provided path a folder in the mods location folder?
    return !path.isEmpty() && QDir(MODS_LOCATION).cd(path);
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
