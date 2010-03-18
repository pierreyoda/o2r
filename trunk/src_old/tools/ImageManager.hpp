#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"

class ImageManager : public ResourceManager< sf::Image > {
private:
protected:
    virtual sf::Image* load( const std::string& strId );
public:
};

extern ImageManager gImageManager;

#endif /* IMAGEMANAGER_H_INCLUDED */

