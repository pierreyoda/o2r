#include <stdlib.h>
#include <time.h>
#include <iostream>
#include<sstream>
#include<fstream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;

//SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define Size 24
#define Width Size*32
#define Height Size*32
#define FPS 60
#define PlayerSpeed 12

//un point est un vecteur d'entier
typedef sf::Vector2i Point;

/*****************************
*   classe Node pour A*
*****************************/
class Node : public std::pair<int,int>
{
    public:
        Node(){first=second=pound_g=pound_h=pound_f=0;}
        Node(Point p)
        {
            first=p.x;
            second=p.y;
            pound_g=pound_h=pound_f=0;
        }
        unsigned int pound_g, pound_h, pound_f;

};

#include "entity.hpp"
#include "case.hpp"
#include "graph.hpp"


/*****************************
*   coeur de l'application
*****************************/
class Core
{
    public:
        static Core core;
        Core();
        void run();
    private:
        Graph graph;

};
