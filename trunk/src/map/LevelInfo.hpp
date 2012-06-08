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

#ifndef LEVELINFO_HPP
#define LEVELINFO_HPP

#include <QDate>
#include <QFileInfo>

/** LevelInfo contains all the informations needed in order to form a complete level.
*Contains : name, author, creation date, (optional) external LES file.
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
