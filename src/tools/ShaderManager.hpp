#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

class ShaderManager : public ResourceManager< sf::Shader >
{
    protected:
        virtual sf::Shader* load(const std::string& strId);
};

extern ShaderManager gShaderManager;

#endif /* SHADERMANAGER_HPP */
