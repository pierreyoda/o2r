#include <iostream>
#include "ImageManager.hpp"
#include "Logger.hpp"

ImageManager gImageManager;

sf::Image *ImageManager::load(const std::string& strId)
{
    sf::Image *image = new sf::Image();
    if(!image->LoadFromFile(strId))
    {
        gLog << "[WARN] ImageManager failed to load: " << strId << "\n";
        /*delete image;
        image = 0;*/
        image->Create(16, 16, sf::Color::White);
    }
    return image;
}
