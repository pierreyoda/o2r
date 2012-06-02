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

#ifndef FILESPATHPROVIDER_HPP
#define FILESPATHPROVIDER_HPP

#include <QDir>
#include <QMap>

/** Set of fonctions providing an asset filepath from an asset ID.
*
*Builds its asset list from the enabled "mods" folders.
*Internally uses Qt classes (QDir, QFileInfo...).
*/
namespace FilespathProvider
{
    /** Refresh the assets list.
    *Order is : main mod / then mod 1 then mod 2... overwriting if needed.
    *Warning : the current list will be erased.
    *@see setAssetsNameFilters() setModsLocation() setMainModFolder()  addMods()
    */
    void refreshAssetsList();

    /** Get the main mod path.
    *@return Main mod path.
    *@see setMainModFolder()
    */
    QString mainModPath();
    /** Set the main mod folder.
    *@param folder Main mod folder (relative to the mods location).
    *@see mainModPath() modsLocation()
    */
    void setMainModFolder(const QString &folder);

    /** Get the mods list.
    *@return Mods list (does not include the main mod).
    *@see addMods()
    */
    const QStringList &modsList();

    /** Add mods to the mods list. Each mod will first be checked by isModValid() function.
    *@param mods Mods to add.
    *@param resetModsList Reset mods list first?
    *@see modsList() isModValid()
    */
    void addMods(const QStringList &mods, bool resetModsList);

    /** Is the given path a valid mod?
    *To be valid the given path must be an existing and readable folder in the mods location.
    *@param path Mod's path.
    *@return True if mod is valid, false otherwise.
    *@see modsLocation()
    */
    bool isModValid(const QString &path);

    /** Get the mods location. May be a relative or absolute path.
    *@return Mods location.
    *@see setModsLocation()
    */
    QString modsLocation();
    /** Set the mods location. May be a relative or absolute path.
    *@param path New mods location.
    *@see modsLocation()
    */
    void setModsLocation(const QString &path);

    /** Set the assets name filters, used when retrieving all the assets in refreshAssetsList().
    *By default : "*", @a i.e. accepts all files.
    *@param nameFilters List of name filters.
    *@see refreshAssetsList()
    */
    void setAssetsNameFilters(const QStringList &nameFilters);
};

#endif // FILESPATHPROVIDER_HPP
