#ifndef CATASTAR_HPP
#define CATASTAR_HPP

#include <map>
#include <list>
#include <utility>
#include "Level.hpp"

struct Node
{
    float gCost, hCost, fCost;
    std::pair<int,int> parent;
};

struct Point
{
    Point(const int &cx = 0, const int &cy = 0) : x(cx), y(cy)
    { }
    int x, y;
};

typedef std::map< std::pair<int,int>, Node> l_node;

/**
* Come from : http://khayyam.developpez.com/articles/algo/astar/
*Developpez.com / Thanks to khayyam.
*/
class CatAStar
{
    public:
        CatAStar(const Level &level);

        std::list<Point> aStar(const Point &catpos, const Point &end);

    private:
        void recoverPath();
        void addAdjacentCases(const std::pair <int,int> &n);
        void addToClosedList(const std::pair<int,int> &p);
        float distance(const int &x1, const int &y1, const int &x2, const int &y2) const;
        bool alreadyInList(const std::pair<int,int> &n, l_node &l) const;
        std::pair<int,int> bestNode(l_node &l) const;

        l_node openList, closedList;
        Node start;
        Point arrival;
        const Level &lvl;
        std::list<Point> path;
};

#endif /* CATASTAR_HPP */
