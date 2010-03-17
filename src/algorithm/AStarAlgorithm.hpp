/**
* AStarAlgorithm utility class for Open Rodent's Revenge.
* Adapted from 'chaos' (http://www.sfml-dev.org/forum-fr/viewtopic.php?t=2523).
*/

#ifndef ASTARALGORITHM_HPP
#define ASTARALGORITHM_HPP

#include <list>
#include "../Level.hpp"

typedef sf::Vector2i Point;
typedef std::list<Point> cpath;
typedef std::pair<int, int> ipair;

class Node : public ipair
{
    public:
        Node() { first=second=pound_g=pound_h=pound_f = 0;}
        Node(Point p)
        {
            first=p.x;
            second=p.y;
            pound_g=pound_h=pound_f=0;
        }
        unsigned int pound_g, pound_h, pound_f;

};

typedef std::map<ipair, Node> l_list;

class AStarAlgorithm
{
        public:
            AStarAlgorithm();
            ~AStarAlgorithm();

             static cpath *pathfinding(const Point &start, const Point &end,
                                     const Level &lvl);
             static unsigned int pound(const Point &pos1, const Point &pos2);

        private:
            static void addAjacentCases(l_list &open, l_list &close,
                        ipair &pos, const Point &end, const Level &lvl);
            static void addNext(const ipair &next, ipair &n, l_list& open,
                         l_list &close, const Point &end);
            static inline unsigned int pound(const int &x1, const int &y1,
                                             const int &x2, const int &y2);
            static inline bool isClear(const int &x, const int &y, const Level &lvl);
            static ipair bestNode(const l_list &l);
};

#endif /* ASTARALGORITHM_HPP */
