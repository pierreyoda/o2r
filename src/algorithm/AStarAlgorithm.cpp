#include <map>
#include "AStarAlgorithm.hpp"

using namespace std;

AStarAlgorithm::AStarAlgorithm()
{

}

AStarAlgorithm::~AStarAlgorithm()
{

}

cpath *AStarAlgorithm::pathfinding(const Point &start, const Point &end,
                                 const Level &lvl)
{
    map<ipair, Node> open;
    map<ipair, Node> close;
    cpath *path = new cpath();
    ipair current;
        current.first  = start.x;
        current.second = start.y;
    close[current] = Node(start);

    /*if (isClear(current.first - 1, current.second, lvl))
        addNext(ipair(current.first - 1, current.second), current, open, close ,end);
    if (isClear(current.first, current.second - 1, lvl))
        addNext(ipair(current.first, current.second - 1), current, open, close ,end);
    if (isClear(current.first + 1, current.second, lvl))
        addNext(ipair(current.first + 1, current.second), current, open, close ,end);
    if (isClear(current.first, current.second + 1, lvl))
        addNext(ipair(current.first , current.second + 1), current, open, close ,end);*/
    addAjacentCases(open, close, current, end, lvl);

    while (!(current.first == end.x && current.second == end.y) && !open.empty())
    {
        current = bestNode(open);

        close[current] = open[current];
        open.erase(current);

        addAjacentCases(open, close, current, end, lvl);
    }

    if ((current.first != end.x) || (current.second != end.y))
        return path;

    Node &tmp = close[std::pair<int, int>(end.x,end.y)];
    Point n;
    n.x = end.x;
    n.y = end.y;
    path->push_front(n);

    while (tmp != pair<int,int>(start.x,start.y))
    {
        n.x = tmp.first;
        n.y = tmp.second;
        path->push_front(n);
        tmp = close[tmp];
    }
    return path;
}

void AStarAlgorithm::addAjacentCases(l_list &open, l_list &close,
                ipair &pos, const Point &end, const Level &lvl)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (j != 0 && isClear(pos.first - i, pos.second - j, lvl))
                addNext(ipair(pos.first - i, pos.second - j), pos, open,
                        close, end);
        }
    }
}

void AStarAlgorithm::addNext(const ipair &next, ipair &n, l_list& open,
                l_list &close, const Point &end)
{
    Node tmp;
    //Si le noeud n'est pas présent
    if (close.find(next) == close.end())
    {
        tmp.pound_g = close[n].pound_g + 1;
        tmp.pound_h = pound(next.first,next.second,end.x, end.y);
        tmp.pound_f = tmp.pound_g + tmp.pound_h;
        tmp.first = n.first;
        tmp.second = n.second;
        if (open.find(next) != open.end())
        {
            if (tmp.pound_f < open[next].pound_f)
                open[next] = tmp;

        }
        else
            open[pair<int,int>(next.first, next.second)] = tmp;
    }
}

unsigned int AStarAlgorithm::pound(const Point &pos1, const Point &pos2)
{
    return pound(pos1.x, pos1.y, pos2.x, pos2.y);
}

unsigned int AStarAlgorithm::pound(const int &x1, const int &y1, const int &x2,
                                   const int &y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

bool AStarAlgorithm::isClear(const int &x, const int &y, const Level &lvl)
{
    return (lvl.getCaseType(x, y) == NOTHING);
}

ipair AStarAlgorithm::bestNode(const l_list &l)
{
    unsigned int m_poundf = l.begin()->second.pound_f;
    ipair m_node = l.begin()->first;
    for (l_list::const_iterator it = l.begin(); it!=l.end(); ++it)
    {
        if (it->second.pound_f < m_poundf)
        {
            m_poundf = it->second.pound_f;
            m_node = it->first;
        }
    }
    return m_node;
}
