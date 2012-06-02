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

/** \brief Provides an asset relative filepath from an asset ID.
*
*Builds its asset list from the enabled "mods" folders.
*Internally uses QDir from Qt but this can be easily changed.
*/
class FilespathProvider
{
public:
    FilespathProvider();

    static std::string mainModPath();
    static void setMainModFolder(const std::string &folder);
    static bool isModValid(const std::string &path);
    static std::string modsLocation();
    static void setModsLocation(const std::string &path);

private:
    static QDir MAIN_MOD_FOLDER;
    static QDir MODS_LOCATION;
};

#endif // FILESPATHPROVIDER_HPP
