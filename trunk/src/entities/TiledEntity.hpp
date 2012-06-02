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

#include <SFML/Graphics/Texture.hpp>
#include <QSharedPointer>

/** \brief A TiledEntity consists of a single texture with a fixed size.
*
*/
class TiledEntity
{
public:
    TiledEntity(int x, int y, const std::string &imageId);

    void setImageId(const std::string &imageId);
    void reloadTexture();

    int x() const { return mX; }
    int y() const { return mY; }

protected:
    int mX;
    int mY;

private:
    std::string mImageId;
    QSharedPointer<sf::Texture> mTexturePtr;
};

#endif // TILEDENTITY_HPP
