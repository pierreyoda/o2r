#include <iostream>
#include <cmath>
#include "CatAStar.hpp"
#include "constantes.hpp"

using namespace std;

CatAStar::CatAStar(const Level &level) : openList(), closedList(), start(),
    arrival(), lvl(level), path()
{

}

std::list<Point> CatAStar::aStar(const Point &catpos, const Point &end)
{
    arrival.x = end.x, arrival.y = end.y;
    start.parent.first  = catpos.x, start.parent.second = catpos.y;

    pair <int,int> current;
    current.first  = catpos.x;
    current.second = catpos.y;

    openList[current]=start;
    addToClosedList(current);
    addAdjacentCases(current);

    while( !((current.first == arrival.x) && (current.second == arrival.y))
            && (!openList.empty()))
    {
        current = bestNode(openList);
        addToClosedList(current);
        addAdjacentCases(current);
    }

    if ((current.first == arrival.x) && (current.second == arrival.y))
    {
        recoverPath();
        return path;
    }
    return std::list<Point>();
}

void CatAStar::recoverPath()
{
    Node &tmp = closedList[pair<int, int>(arrival.x, arrival.y)];

    Point n(arrival.x, arrival.y);
    pair<int,int> prec;
    prec.first  = tmp.parent.first;
    prec.second = tmp.parent.second;
    path.push_front(n);

    while (prec != pair<int,int>(start.parent.first, start.parent.first))
    {
        n.x = prec.first, n.y = prec.second;
        path.push_front(n);

        tmp = closedList[tmp.parent];
        prec.first  = tmp.parent.first;
        prec.second = tmp.parent.second;
    }
}

void CatAStar::addAdjacentCases(const pair <int,int> &n)
{
    Node tmp;
    for (int i=n.first-1; i<=n.first+1; i++)
    {
        if ((i<0) || (i>(int)gv.LVL_X))
            continue;
        for (int j=n.second-1; j<=n.second+1; j++)
        {
            if ((j<0) || (j>(int)gv.LVL_Y))
                continue;
            if ((i==n.first) && (j==n.second))
                continue;
            CASETYPE casetype = lvl.getCaseType(i, j);
            if (casetype != NOTHING)
                continue;

            pair<int,int> it(i,j);
            if (!alreadyInList(it, closedList))
            {
                tmp.gCost = closedList[n].gCost + distance(i,j,n.first,n.second);
                tmp.hCost = distance(i,j,arrival.x,arrival.y);
                tmp.fCost = tmp.gCost + tmp.hCost;
                tmp.parent = n;

                if (alreadyInList(it, openList))
                {
                    if (tmp.fCost < openList[it].fCost)
                        openList[it]=tmp;
                }
                else
                    openList[pair<int,int>(i,j)]=tmp;
            }
        }
    }
}

void CatAStar::addToClosedList(const pair<int,int> &p)
{
    Node &n = openList[p];
    closedList[p]=n;
    if (openList.erase(p)==0)
        cerr << "Error, node does not appear in the list open, cannot remove."
                << endl;
    return;

}

float CatAStar::distance(const int &x1, const int &y1, const int &x2,
                                const int &y2) const
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    /* ^2 (faster) : */
    /* return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2); */
}

bool CatAStar::alreadyInList(const pair<int,int> &n, l_node &l) const
{
    l_node::iterator i = l.find(n);
    if (i == l.end())
        return false;
    else
        return true;
}

pair<int,int> CatAStar::bestNode(l_node &l) const
{
    float fCost = l.begin()->second.fCost;
    pair<int,int> node = l.begin()->first;

    for (l_node::iterator i = l.begin(); i!=l.end(); i++)
    {
        if (i->second.fCost < fCost)
        {
            fCost = i->second.fCost;
            node = i->first;
        }
      }

    return node;
}

