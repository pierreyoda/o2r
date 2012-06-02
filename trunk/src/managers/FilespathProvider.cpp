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

QDir FilespathProvider::MAIN_MOD_FOLDER("");
QDir FilespathProvider::MODS_LOCATION("");

FilespathProvider::FilespathProvider()
{

}

std::string FilespathProvider::mainModPath()
{
    return MAIN_MOD_FOLDER.path().toStdString();
}

void FilespathProvider::setMainModFolder(const std::string &folder)
{
    if (isModValid(folder))
    {
        MAIN_MOD_FOLDER = MODS_LOCATION;
        MAIN_MOD_FOLDER.cd(QString::fromStdString(folder));
        QLOG_INFO() << "FilespathProvider : main mod set to"
                    << MAIN_MOD_FOLDER.path() << ".";
    }
    else
    {
        QLOG_ERROR() << "FilespathProvider : cannot set main mod to"
                     << QString::fromStdString(folder)
                     << ": invalid mod.";
    }
}

bool FilespathProvider::isModValid(const std::string &path)
{
    // Is the mods location defined and existing?
    if (!MODS_LOCATION.exists())
    {
        QLOG_ERROR() << "FilespathProvider : undefined mods location.";
        return false;
    }
    // Is the provided path a folder in the mods location folder?
    return QDir(MODS_LOCATION).cd(QString::fromStdString(path));
}

std::string FilespathProvider::modsLocation()
{
    return MODS_LOCATION.path().toStdString();
}

void FilespathProvider::setModsLocation(const std::string &path)
{
    QDir temp(QString::fromStdString(path));
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
