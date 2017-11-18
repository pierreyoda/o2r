#include "TilesTypesManager.hpp"
#include "../game/EditorScreen.hpp"
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
    if (c.isNull() || c == ' ' || textureAlias.isEmpty() || type.isEmpty())
    {
        QLOG_WARN() << "TilesTypesManager : cannot add invalid tile type"
                    << log.toLocal8Bit().constData();
        return;
    }
    if (c == EditorScreen::MOUSE_POS_CHAR)
    {
        QLOG_WARN() << "TilesTypesManager : cannot add tile type"
                    << log.toLocal8Bit().constData()
                    << ": same character as mouse position";
        return;
    }
    TILES_TYPES[c] = TileInfo(textureAlias, type);
    QLOG_INFO() << "TilesTypesManager : defined tile type"
                << log.toLocal8Bit().constData();
}

const QMap<QChar, TileInfo> &getMap()
{
    return TILES_TYPES;
}

} // namespace TilesTypesManager
