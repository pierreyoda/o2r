#include <iostream>
#include "ImageManager.hpp"

using namespace std;

ImageManager gImageManager;

sf::Image* ImageManager::load( const std::string& strId )
{
    sf::Image* image = new sf::Image();
    if( !image->LoadFromFile( strId ) )
    {
        cerr << "[WARN] ImageManager failed to load: " << strId << "\n";
        /*delete image;
        image = NULL;*/
        image->Create(16, 16, sf::Color::White);
    }
    return image;
}
