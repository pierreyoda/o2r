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
#include "AssetsManager.hpp"
#include "FilespathProvider.hpp"
#include "QsLog.h"

namespace AssetsManager
{

namespace
{
    QMap<QString, TexturePtr> TEXTURE_MAP;
} // anonymous namespace



/** \internal Search for a texture in the AssetsManager's texture map.
*@return Pointer to the texture (null if not found).
*/
TexturePtr findTexture(const QString &path)
{
    return TEXTURE_MAP.value(path, TexturePtr());
}

/** \internal Load the requested texture.
*@return Pointer to the texture (null if failed).
*/
TexturePtr loadTexture(const QString &path)
{
    sf::Texture *texture = new(std::nothrow) sf::Texture();
    if (texture == 0 || !texture->loadFromFile(path.toStdString()))
    {
        delete texture;
        return TexturePtr();
    }
    return TexturePtr(texture);
}

TexturePtr getTexture(const QString &path, bool isAlias)
{
    QString texturePath = isAlias ?
                FilespathProvider::assetPathFromAlias(path) : path;
    TexturePtr texture = findTexture(texturePath);
    // Texture already loaded
    if (!texture.isNull())
        return texture;
    // Texture must be loaded
    texture = loadTexture(texturePath);
    if (!texture.isNull())
    {
        TEXTURE_MAP[texturePath] = texture;
        QLOG_INFO() << "AssetsManager : loaded texture" << texturePath << ".";
        return texture;
    }
    // Cannot load the texture
    QLOG_ERROR() << "AssetsManager : cannot load texture" << texturePath << ".";
    return TexturePtr();
}

void clearTextureCache()
{
    QLOG_INFO() << "AssetsManager : cleared texture cache.";
    TEXTURE_MAP.clear();
}

} // namespace AssetsManager
