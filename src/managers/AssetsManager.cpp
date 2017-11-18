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
