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

#include "HudRectangle.hpp"
#include "../GameCanvas.hpp"

const sf::Color FILL_COLOR(150, 150, 150);
const unsigned int HudRectangle::HEIGHT = 60;

HudRectangle::HudRectangle()
{
    mRectangleShape.setFillColor(FILL_COLOR);
}

void HudRectangle::setWidth(unsigned int width)
{
    mRectangleShape.setSize(sf::Vector2f(width, HEIGHT));
}

void HudRectangle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mRectangleShape, states);
}
