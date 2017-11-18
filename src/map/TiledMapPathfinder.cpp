#include <cmath>
#include "TiledMapPathfinder.hpp"
#include "TiledMap.hpp"
#include "QsLog.h"

using namespace micropather;

TiledMapPathfinder::TiledMapPathfinder(const TiledMap &level) : mLevelRef(level),
    mSolver(this)
{
}

TiledMapPathfinder::~TiledMapPathfinder()
{

}

int TiledMapPathfinder::computePath(const sf::Vector2i &start,
                                    const sf::Vector2i &end,
                                    std::vector<void*> &path)
{
    float totalCost;
    path.clear();
    return mSolver.Solve(posToState(start), posToState(end), &path, &totalCost);
}

void TiledMapPathfinder::reset()
{
    mSolver.Reset();
}

float TiledMapPathfinder::LeastCostEstimate(void *stateStart, void *stateEnd)
{
    const sf::Vector2i start = stateToPos(stateStart), end = stateToPos(stateEnd);
    const sf::Vector2i delta(end.x-start.x, end.y-start.y);
    return /*sqrt*/(delta.x*delta.x + delta.y*delta.y); // Euclidean distance (square is used here for better performances)
}

void TiledMapPathfinder::AdjacentCost(void *state, std::vector<StateCost> *adjacent)
{
    sf::Vector2i pos = stateToPos(state);
    // Initial check
    if (!mLevelRef.isInsideMap(pos.x, pos.y))
        return;
    // Look through the 8 adjacent tiles
    for (int i = pos.x-1; i <= pos.x+1; i++)
    {
        for (int j = pos.y-1; j <= pos.y+1; j++)
        {
            // If current pos : ignore
            if (i == pos.x && j == pos.y)
                continue;

            const TileInfo &tileInfo = mLevelRef.getTileInfo(i, j);
            // If outside the map / invalid : ignore
            if (!tileInfo.isValid)
                continue;
            // If uncrossable : ignore
            if (tileInfo.type != TileInfo::TYPE_GROUND)
                continue;
            // Add a new state
            StateCost nodeCost = { posToState(sf::Vector2i(i, j)), 1 }; // every tile has the same cost
            //PrintStateInfo(nodeCost.state);
            adjacent->push_back(nodeCost);
        }
    }
}

void TiledMapPathfinder::PrintStateInfo(void *state)
{
    const sf::Vector2i pos = stateToPos(state);
    QLOG_INFO() << QString("(%1, %2)").arg(QString::number(pos.x),
                                           QString::number(pos.y))
                   .toLocal8Bit().constData();
}

sf::Vector2i TiledMapPathfinder::stateToPos(void *state) const
{
    const int index = (int) state, y = index / mLevelRef.sizeX();
    return sf::Vector2i(index - y * mLevelRef.sizeX(), y);
}

void *TiledMapPathfinder::posToState(const sf::Vector2i &pos) const
{
    return (void*) (pos.y * mLevelRef.sizeX() + pos.x);
}
