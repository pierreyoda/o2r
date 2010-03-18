#include <iostream>

#include "ImageManager.hpp"

using namespace std;

ImageManager gImageManager;

sf::Image* ImageManager::load( const std::string& strId ) {
    sf::Image* image = new sf::Image();
    if( !image->LoadFromFile( strId ) ) {
        cout << "[WARN] ImageManager failed to load: " << strId << endl;
        delete image;
        image = NULL;
    }

    return image;
}
