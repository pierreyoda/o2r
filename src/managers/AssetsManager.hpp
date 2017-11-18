#ifndef ASSETSMANAGER_HPP
#define ASSETSMANAGER_HPP

#include <QSharedPointer>
#include <SFML/Graphics/Texture.hpp>

typedef QSharedPointer<sf::Texture> TexturePtr;

/** Set of fonctions managing the game assets.
*/
namespace AssetsManager
{
    /** Get a texture (load it if not already done).
    *@param path Texture name (ex. : "mouse.png").
    *@param isAlias If true, use FilespathProvider to get the texture path. True by default.
    *@return Pointer to the loaded texture.
    *@see FilespathProvider::assetPathFromAlias()
    */
    TexturePtr getTexture(const QString &path, bool isAlias = true);

    /** Clear the texture cache.
    *All used textures should be reloaded through getTexture() then.
    */
    void clearTextureCache();
}

#endif // ASSETSMANAGER_HPP
