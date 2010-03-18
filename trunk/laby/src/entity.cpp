#include "core.hpp"


/*****************************
*   constructeur
*****************************/
Entity::Entity( double speed): sf::Sprite()
{
    this->speed = FPS/speed;
    current = this->speed;
}

/*****************************
*   change la position de l'entité
*****************************/
void Entity::SetPosition(double x, double y)
{
    this->x = x;
    this->y = y;
    sf::Sprite::SetPosition(x*32, y*32);
}

/*****************************
*   constructeur de trésor
*****************************/
Treasure::Treasure() : Entity(0)
{
    sf::Image* img = new sf::Image();
    if(!img->LoadFromFile("coffre.png"))
        exit(EXIT_FAILURE);
    SetImage(*img);
}

/*****************************
*   constructeur de monstre
*****************************/
Monster::Monster() : Entity(PlayerSpeed/2)
{
    sf::Image* img = new sf::Image();
    if(!img->LoadFromFile("Monster.png"))
        exit(EXIT_FAILURE);
    SetImage(*img);
    path = NULL;
}

/*****************************
*   défini la chemin a parcourir
*****************************/
void Monster::SetPath(list<Point>* path)
{
    this->path = path;
}

/*****************************
*   si chemin
*****************************/
bool Monster::HasPath()
{
    return path != NULL && !path->empty();
}

/*****************************
*   prochaine destination
*****************************/
Point Monster::GetNext()
{
    Point first = *path->begin();
    path->pop_front();
    return first;
}

/*****************************
*   constructeur du hero
*****************************/
Hero::Hero() : Entity(PlayerSpeed)
{
    sf::Image* img = new sf::Image();
    if(!img->LoadFromFile("PacMan.png"))
        exit(EXIT_FAILURE);
    SetImage(*img);
}



