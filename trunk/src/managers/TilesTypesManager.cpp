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

#include <QMap>
#include "TilesTypesManager.hpp"
#include "QsLog.h"

const QString TileInfo::TYPE_GROUND = "GROUND";
const QString TileInfo::TYPE_BLOCK = "BLOCK";
const QString TileInfo::TYPE_WALL = "WALL";

namespace TilesTypesManager
{

namespace
{
    QMap<QChar, TileInfo> TILES_TYPES;
    const TileInfo NULL_TILE_INFO;
} // anonymous namespace

TileInfo tileInfoFromChar(const QChar &c)
{
    return TILES_TYPES.value(c, NULL_TILE_INFO);
}

void setType(const QChar &c, const QString &textureAlias,
             const QString &type)
{
    const QString log = QString("character '%1', texture alias \"%2\", type \"%3\"")
            .arg(c, textureAlias, type);
    if (c == ' ' || textureAlias.isEmpty() || type.isEmpty())
    {
        QLOG_WARN() << "TilesTypesManager : cannot add tile type"
                    << log.toLocal8Bit().constData();
        return;
    }
    TILES_TYPES[c] = TileInfo(textureAlias, type);
    QLOG_INFO() << "TilesTypesManager : defined tile type"
                << log.toLocal8Bit().constData();
}

} // namespace TilesTypesManager
