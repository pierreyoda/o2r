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

#include <stdexcept>
#include <QFileInfo>
#include <QStringList>
#include "TiledMapFactory.hpp"
#include "../map/TiledMap.hpp"
#include "../game/EditorScreen.hpp"
#include "QsLog.h"

const unsigned int DSIZE_X = 23, DSIZE_Y = 23;
const QString XML_FILE_SUFFIX("xml");
const QString OPTION_TXT_SIZE_X("x");
const QString OPTION_XML_SIZE_X("sizeX");
const QString OPTION_TXT_SIZE_Y("y");
const QString OPTION_XML_SIZE_Y("sizeY");
const QString OPTION_NAME("name");
const QString OPTION_AUTHOR("author");
const QChar TXT_CHAR_MOUSE = EditorScreen::MOUSE_POS_CHAR;
const QChar TXT_OPTION_SEP('=');
const QChar DEFAULT_TILE('0');

// Return the longest tile line size
unsigned int TiledMapFactory::computeLevelSizeX(const TiledMap &level)
{
    int maxSizeX = 0;
    for (int i = 0; i < level.mTiles.size(); i++)
    {
        const int tilesLineSize = level.mTiles[i].size();
        if (tilesLineSize > maxSizeX)
            maxSizeX = tilesLineSize;
    }
    return maxSizeX;
}

TiledMap *TiledMapFactory::loadLevel(QString path)
{
    TiledMap *level = 0;
    QFile file(path);
    const QFileInfo fileInfo(file);
    try
    {
        if (!fileInfo.exists())
            throw std::runtime_error("file does not exists");
        if (fileInfo.suffix() == XML_FILE_SUFFIX)
            level = loadMapXmlFormat(file);
        else
            level = loadMapTxtFormat(file);
        if (level == 0)
            throw std::runtime_error("reading error");

        // Level size fix
        unsigned int &sizeX = level->mSizeX, &sizeY = level->mSizeY; // (un)defined sizes
        const unsigned int cSizeX = computeLevelSizeX(*level), // computed sizes
                cSizeY = level->mTiles.size();
        if (sizeX == 0)
        {
            sizeX = cSizeX;
            QLOG_WARN() << "No level X size specified : setting X size to"
                        << sizeX;
        }
        else if (sizeX != cSizeX)
        {
            sizeX = cSizeX;
            QLOG_WARN() << "Incorrect specified level X size : setting X size to"
                        << sizeX;
        }
        if (sizeY == 0)
        {
            sizeY = cSizeY;
            QLOG_WARN() << "No level Y size specified : setting Y size to"
                        << sizeY;
        }
        else if (sizeY != static_cast<unsigned int>(level->mTiles.size()))
        {
            sizeY = cSizeY;
            QLOG_WARN() << "Incorrect specified level Y size : setting Y size to"
                        << sizeY;
        }

        LevelInfo &info = level->mInfo;

        // Level path
        info.filePath = path;

        // Level author
        if (info.author.isEmpty())
            QLOG_WARN() << "No author specified.";
        else
            QLOG_INFO() << QString("Author is \"%1\"").arg(info.author)
                           .toLocal8Bit().constData();
    }
    catch (const std::exception &e)
    {
        QLOG_ERROR() << "TiledMapFactory : cannot load level"
                     << fileInfo.filePath()
                     << ":" << e.what() << ".";
        delete level;
        return 0;
    }
    return level;
}

TiledMap *TiledMapFactory::loadMapTxtFormat(QFile &file)
{
    TiledMap *lvl = new TiledMap(0, 0);
    LevelInfo lvlInfo;
    // Open level file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("file not readable");
    QTextStream in(&file);
    unsigned int lineCount = 0, nbOfOptions = 0;
    while (!in.atEnd())
    {
        // Read the line
        QString line = in.readLine();
        // If empty : ignore
        if (line.isEmpty())
            continue;
        // Increment line number
        ++lineCount;
        // If option : interpret
        Option option = processTxtOptionLine(line);
        if (!option.first.isEmpty())
        {
            if (!interpretOption(option, *lvl, true))
                QLOG_WARN() << "TiledMapFactory : invalid level option ( name ="
                            << option.first << " value =" << option.second << ").";
            ++nbOfOptions;
        }
        // Else : interpret line of tiles
        else if (!processTilesLine(line, *lvl, lineCount-nbOfOptions, true))
                throw std::runtime_error(QString("invalid tiles line n°%1 (\"%2\")")
                                         .arg(QString::number(lineCount-nbOfOptions),
                                              line).toStdString());
    }
    QLOG_INFO() << QString("TiledMapFactory : finished reading TXT level (%1 tiles lines and %2 options lines)")
                   .arg(QString::number(lineCount-nbOfOptions),
                        QString::number(nbOfOptions)).toLocal8Bit().constData();
    // Close level file
    file.close();

    return lvl;
}

TiledMap *TiledMapFactory::loadMapXmlFormat(QFile &file)
{
    return 0;
}

// Ex. : "X=35" ==> Option("X", "35")
Option TiledMapFactory::processTxtOptionLine(const QString &line)
{
    QStringList split = line.split(TXT_OPTION_SEP, QString::KeepEmptyParts);
    if (split.size() > 1)
        return Option(split.at(0), split.at(1));
    return Option();
}

bool TiledMapFactory::interpretOption(const Option &option, TiledMap &lvl,
                                      bool oldFormat)
{
    if (option.first.isEmpty() || option.second.isEmpty())
        return false;
    LevelInfo &info = lvl.mInfo;
    // X size
    if (QString::compare(option.first,
                         oldFormat? OPTION_TXT_SIZE_X : OPTION_XML_SIZE_X,
                         Qt::CaseInsensitive) == 0)
    {
        bool ok = false;
        unsigned int number = option.second.toUInt(&ok);
        if (ok)
        {
            if (number < TiledMap::SIZE_MAX_LIMIT_X)
            {
                lvl.mSizeX = number;
                QLOG_INFO() << "Level X size set to" << number << ".";
            }
            else
            {
                lvl.mSizeX = number;
                QLOG_WARN() << QString("Excessive X level size (%1) : level X size set to limit (%2)")
                               .arg(QString::number(number),
                                    QString::number(TiledMap::SIZE_MAX_LIMIT_X))
                               .toLocal8Bit().constData();
            }
            return true;
        }
        else
            return false;
    }
    // Y size
    else if (QString::compare(option.first,
                              oldFormat? OPTION_TXT_SIZE_Y : OPTION_XML_SIZE_Y,
                              Qt::CaseInsensitive) == 0)
    {
        bool ok = false;
        unsigned int number = option.second.toUInt(&ok);
        if (ok)
        {
            if (number < TiledMap::SIZE_MAX_LIMIT_X)
            {
                lvl.mSizeY = number;
                QLOG_INFO() << "Level Y size set to" << number << ".";
            }
            else
            {
                lvl.mSizeY = number;
                QLOG_WARN() << QString("Excessive Y level size (%1) : level Y size set to limit (%2)")
                               .arg(QString::number(number),
                                    QString::number(TiledMap::SIZE_MAX_LIMIT_Y))
                               .toLocal8Bit().constData();
            }
            return true;
        }
        else
            return false;
    }
    // Author
    else if (option.first == OPTION_AUTHOR)
    {
        info.author = option.second;
        return true;
    }
    // Name
    else if (option.first == OPTION_NAME)
    {
        info.name = option.second;
        return true;
    }

    return false;
}

bool TiledMapFactory::processTilesLine(const QString &line, TiledMap &lvl,
                                       unsigned int lineNb, bool oldFormat)
{
    QList<Tile> tilesLine;
    for (int i = 0; i < line.size(); i++)
    {
        const QChar c = line.at(i);
        // Old format : if mouse pos, place the mouse and add a default tile there
        if (oldFormat && QString::compare(c, TXT_CHAR_MOUSE, Qt::CaseInsensitive)
                == 0)
        {
            lvl.mInfo.mousePosX = i, lvl.mInfo.mousePosY = lineNb-1;
            tilesLine.append(Tile(i, lineNb-1, DEFAULT_TILE, false));
        }
        // Invalid tile : place default tile
        else if (c.isNull() || c == ' ')
            tilesLine.append(Tile(i, lineNb-1, DEFAULT_TILE, false));
        // Valid tile : place the tile
        else
            tilesLine.append(Tile(i, lineNb-1, c, false));
    }
    lvl.mTiles.append(tilesLine);
    return true;
}

bool TiledMapFactory::saveLevel(TiledMap &level, QString path)
{
    // File extension check
    const QString suffix = path.section('.', -1);
    if (suffix.isEmpty())
    {
        QLOG_ERROR() << QString("TiledMapFactory : cannot save level to \"%1\" (invalid extension).")
                        .arg(path).toLocal8Bit().constData();
        return false;
    }
    // Save the level
    bool success = false;
    level.mInfo.filePath = path;
    if (suffix == XML_FILE_SUFFIX)
        success = saveMapXmlFormat(level);
    else
        success = saveMapTxtFormat(level);
    if (!success)
    {
        QLOG_ERROR() << QString("TiledMapFactory : cannot save level to \"%1\" (writing error).")
                        .arg(path).toLocal8Bit().constData();
        return false;
    }
    return true;
}


bool TiledMapFactory::saveMapTxtFormat(const TiledMap &level)
{
    const LevelInfo &info = level.info();
    QFile file(info.filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);

    // Write options
    out << formTxtOptionLine(OPTION_TXT_SIZE_X, QString::number(level.sizeX()));
    out << formTxtOptionLine(OPTION_TXT_SIZE_Y, QString::number(level.sizeY()));
    if (!info.name.isEmpty())
        out << formTxtOptionLine(OPTION_NAME, info.name);
    if (!info.author.isEmpty())
        out << formTxtOptionLine(OPTION_AUTHOR, info.author);

    // Write lines of tiles
    const QList< QList<Tile> > &tiles = level.mTiles;
    for (int i = 0; i < tiles.size(); i++)
    {
        const QList<Tile> &list = tiles[i];
        for (int j = 0; j < list.size(); j++)
        {
            // Old format : place mouse pos char ('m' or 'M') if no random pos
            if (j == info.mousePosX && i == info.mousePosY && !info.mouseRandomPos)
                out << TXT_CHAR_MOUSE;
            // Place a tile char
            else
            {
                const Tile &tile = list[j];
                out << tile.getChar();
            }
        }
        // avoid empty line at the end (not really important though)
        if (i != tiles.size())
            out << "\n";
    }
    QLOG_INFO() << QString("TiledMapFactory : finished saving TXT level to \"%1\".")
                   .arg(info.filePath).toLocal8Bit().constData();

    return true;
}

QString TiledMapFactory::formTxtOptionLine(const QString &name, const QString &value)
{
    return QString(name + TXT_OPTION_SEP + value + '\n');
}

bool TiledMapFactory::saveMapXmlFormat(const TiledMap &level)
{
    QFile file(level.info().filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    return false;
}

