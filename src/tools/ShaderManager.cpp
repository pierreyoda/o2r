#include <iostream>
#include "ShaderManager.hpp"
#include "Logger.hpp"

using namespace std;

ShaderManager gShaderManager;

sf::Shader* ShaderManager::load( const std::string& strId)
{
    sf::Shader* shader = new sf::Shader();
    if( !shader->LoadFromFile( strId ) )
    {
        gLog << "[WARN] ShaderManager failed to load: " << strId << "\n";
        delete shader;
        shader = NULL;
    }
    return shader;
}
