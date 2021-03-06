#ifndef TILEDENTITY_HPP
#define TILEDENTITY_HPP

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "../managers/AssetsManager.hpp"

/** A TiledEntity consists of a single texture with a fixed size.
*
*/
class TiledEntity : public sf::Drawable
{
public:
    /** Default constructor.
    *@param x X position (in tiles units).
    *@param y Y position (in tiles units).
    *@param textureAlias Texture alias.
    *@see FilespathProvider::assetPathFromAlias()
    */
    TiledEntity(int x, int y, const QString &textureAlias);

    virtual ~TiledEntity();

    /** Change the texture alias and load the associated texture.
    *@param textureAlias New texture alias.
    *@see loadTexture() FilespathProvider::assetPathFromAlias()
    *@return True if successful, false otherwise.
    */
    bool setTextureAlias(const QString &textureAlias);

    /** (Re)load the texture.
    *Must be called at least once, AFTER having set the main mod.
    *@see setTextureAlias() AssetsManager::getTexture()
    *@return True if successful, false otherwise.
    */
    bool loadTexture();

    /** Get the texture.
    *@return Smart pointer to the used sf::Texture.
    */
    TexturePtr getTexture();

    /** Draw the TiledEntity to the given sf::RenderTarget.
    *Implements the abstract function from sf::Drawable.
    *@param target Target where the TiledEntity must be drawn.
    *@param states Current render states.
    *
    *Note : should be called only for dynamic entities (likely to move often), static ones (such as Tile)
    *can be rendered once by grouping all the vertices in a single sf::VertexArray (if they all use the same texture).
    */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const;

    /** Get the X position.
    *@return X position, in tiles units.
    */
    int x() const { return mX; }

    /** Get the Y position.
    *@return Y position, in tiles units.
    */
    int y() const { return mY; }

    /** Set the X position.
    *@param x X position, in tiles units.
    *@return Reference to the TiledEntity.
    */
    TiledEntity &setX(int x) { mX = x; return *this; }

    /** Set the Y position.
    *@param y Y position, in tiles units.
    *@return Reference to the TiledEntity.
    */
    TiledEntity &setY(int y) { mY = y; return *this; }


    /** Tile size. A size of 16 means that every tile entities' textures must have a size of 16x16 pixels.
    */
    static const unsigned int TILE_SIZE;

    /** Default vertices, used in rendering.
    *@see draw()
    */
    static const sf::Vertex VERTICES[4];

protected:
    int mX;
    int mY;

private:
    QString mTextureAlias;
    TexturePtr mTexturePtr;
};

#endif // TILEDENTITY_HPP
