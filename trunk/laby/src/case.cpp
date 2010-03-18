#include "core.hpp"

/*****************************
*   constructeur d'une case
*****************************/
Case::Case(sf::Vector2f vector) : sf::Sprite(Graph::wall, vector)
{
    clear = false;
}

/*****************************
*   enleve le mur
*****************************/
void Case::Clear()
{
    clear = true;
    SetImage(Graph::clear);
}

/*****************************
*   si il y a un mur
*****************************/
bool Case::IsClear()
{
    return clear;
}
