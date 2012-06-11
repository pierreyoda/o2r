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
    *@param target Target where the TiledEntity is drawn.
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
