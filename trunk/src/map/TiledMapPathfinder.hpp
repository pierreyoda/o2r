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

#ifndef TILEDMAPPATHFINDER_HPP
#define TILEDMAPPATHFINDER_HPP

#include <vector>
#include <QList>
#include <SFML/System/Vector2.hpp>
#include <stdint.h> // needed by micropather
#include "micropather/micropather.h"

class TiledMap;
typedef QList<sf::Vector2i> TilePosList;

/** Pathfinding class able to compute a path between a start and an end positions.
*Uses the MicroPather library (http://www.grinninglizard.com/MicroPather/).
*/
class TiledMapPathfinder : public micropather::Graph
{
public:
    /** Default constructor.
    *@param level Reference to the level where the path will be searched.
    */
    TiledMapPathfinder(const TiledMap &level);
    ~TiledMapPathfinder();

    /** Find a path between start and end positions in the given map.
    *@param start Start position.
    *@param end End position.
    *@param path Reference to the result path (vector of positions, in raw micropather states).
    *@return The result ID.
    *Empty if not found.
    */
    int computePath(const sf::Vector2i &start, const sf::Vector2i &end,
                    std::vector<void*> &path);

    /** Must be called whenever the map change.
    */
    void reset();

    /** @internal Needed by micropather.
    */
    float LeastCostEstimate(void *stateStart, void *stateEnd);

    /** @internal Needed by micropather.
    */
    void AdjacentCost(void *state, std::vector<micropather::StateCost> *adjacent);

    /** @internal Needed by micropather.
    */
    void PrintStateInfo(void *state);

    sf::Vector2i stateToPos(void *state) const;
    void *posToState(const sf::Vector2i &pos) const;

private:
    const TiledMap &mLevelRef;
    micropather::MicroPather mSolver;
};

#endif // TILEDMAPPATHFINDER_HPP
