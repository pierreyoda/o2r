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

#ifndef TILEDMAPFACTORY_HPP
#define TILEDMAPFACTORY_HPP

#include <QPair>
#include <QFile>

class TiledMap;

typedef QPair<QString, QString> Option;

/** Static class able to load/save a TiledMap.
*
* @see TiledMap
*/
struct TiledMapFactory
{
    static unsigned int computeLevelSizeX(const TiledMap &level);

    static TiledMap *loadLevel(QString path);

    static bool saveLevel(TiledMap &level, QString path);

private:
    // Load
    static TiledMap *loadMapTxtFormat(QFile &file);
    static Option processTxtOptionLine(const QString &line);

    static TiledMap *loadMapXmlFormat(QFile &file);

    static bool interpretOption(const Option &option, TiledMap &lvl, bool oldFormat);
    static bool processTilesLine(const QString &line, TiledMap &lvl, unsigned int lineNb,
                                 bool oldFormat);

    // Save
    static bool saveMapTxtFormat(const TiledMap &level);
    static QString formTxtOptionLine(const QString &name, const QString &value);

    static bool saveMapXmlFormat(const TiledMap &level);
};

#endif // TILEDMAPFACTORY_HPP
