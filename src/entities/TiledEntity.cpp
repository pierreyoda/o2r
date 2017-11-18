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

TiledEntity::TiledEntity(int x, int y, const QString &textureAlias) : mX(x),
    mY(y), mTextureAlias(textureAlias)
{

}

TiledEntity::~TiledEntity()
{
    mTexturePtr.clear();
}

bool TiledEntity::setTextureAlias(const QString &textureAlias)
{
    mTextureAlias = textureAlias;
    return loadTexture();
}

bool TiledEntity::loadTexture()
{
    mTexturePtr = AssetsManager::getTexture(mTextureAlias);
    return !mTexturePtr.isNull();
}

TexturePtr TiledEntity::getTexture()
{
    return mTexturePtr;
}

void TiledEntity::draw(RenderTarget &target, RenderStates states) const
{
    states.transform.translate(mX * TILE_SIZE, mY * TILE_SIZE); // tiles units to pixels
    states.texture = mTexturePtr.data(); // set texture
    target.draw(TiledEntity::VERTICES, 4, Quads, states);
}
