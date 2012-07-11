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

#ifndef HUDRECTANGLE_HPP
#define HUDRECTANGLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

/** Rectangle where all game informations will be displayed (number of lives, score...).
*
*/
class HudRectangle : public sf::Drawable
{
public:
    HudRectangle();

    /** Set the rectangle width. Must be called once.
    *
    *@param w Width.
    */
    void setWidth(unsigned int width);

    /** Draw the TiledEntity to the given sf::RenderTarget.
    *Implements the abstract function from sf::Drawable.
    *@param target Target where the rectangle must be drawn.
    *@param states Current render states.
    */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const;

    static const unsigned int HEIGHT;

private:
    sf::RectangleShape mRectangleShape;
};

#endif // HUDRECTANGLE_HPP
