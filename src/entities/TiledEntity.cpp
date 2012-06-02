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

#include <SFML/Graphics.hpp>
#include "TiledEntity.hpp"

using namespace sf;

const unsigned int TiledEntity::TILE_SIZE = 16;
const Vertex TiledEntity::VERTICES[4]  = {
    Vertex(Vector2f(0, 0), Vector2f(0, 0)),
    Vertex(Vector2f(0, TILE_SIZE), Vector2f(0, TILE_SIZE)),
    Vertex(Vector2f(TILE_SIZE, TILE_SIZE), Vector2f(TILE_SIZE, TILE_SIZE)),
    Vertex(Vector2f(TILE_SIZE, 0), Vector2f(TILE_SIZE, 0))
};

TiledEntity::TiledEntity(int x, int y, const std::string &textureAlias) : mX(x),
    mY(y), mTextureAlias(textureAlias)
{

}

void TiledEntity::setTextureAlias(const std::string &textureAlias)
{
    mTextureAlias = textureAlias;
    loadTexture();
}

void TiledEntity::loadTexture()
{
    mTexturePtr = AssetsManager::getTexture(mTextureAlias);
}

TexturePtr TiledEntity::getTexture()
{
    return mTexturePtr;
}

void TiledEntity::draw(RenderTarget &target, RenderStates states) const
{
    states.transform.translate(mX * TILE_SIZE, mY * TILE_SIZE);
    states.texture = mTexturePtr.data();
    target.draw(TiledEntity::VERTICES, 4, Quads, states);
}
