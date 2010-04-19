#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

class ImageManager : public ResourceManager< sf::Image >
{
    protected:
        virtual sf::Image* load(const std::string& strId);
};

extern ImageManager gImageManager;

#endif /* IMAGEMANAGER_H_INCLUDED */

