#include "Tower.hpp"
#include "LevelFileInterpreter.hpp"
#include "tools/ShaderManager.hpp"

// TODO (Pierre-Yves#1#): [EFFET VISUEL] Ajouter flou progressif (effet profondeur verticale
Tower::Tower() : m_lowerFloorsShader(*gShaderManager.getResource("blur.sfx")),
    m_lowerFloorsShader2(*gShaderManager.getResource("colorize.sfx")),
    m_currentFloor(0), m_stairsDescriptionFlag(stairsDescriptionDefaultFlag),
    m_LesChanged(true)
{
    temp.Create(gv.SCREEN_W, gv.SCREEN_H);
    temp2.Create(gv.SCREEN_W, gv.SCREEN_H);
}

Tower::~Tower()
{
    m_floors.clear();
}

void Tower::render(sf::RenderTarget &target)
{
    for (unsigned int i = 0; i < m_floors.size(); i++)
    {
        bool transparent = true;
        if (m_floors[i].second == NULL)
            continue;
        if (i == 0)
            transparent = false;
        if (m_LesChanged)
            m_floors[i].second->updateCasesImages();
        if (i < m_currentFloor)
        {
            const sf::Image &img  = *m_floors[i].second->getRenderResult(transparent).GetImage();
                temp.Clear();
                temp.Draw(sf::Sprite(img), m_lowerFloorsShader);
                temp2.Clear();
                temp2.Draw(sf::Sprite(temp.GetImage()), m_lowerFloorsShader2);
            target.Draw(sf::Sprite(temp2.GetImage()));
        }
        else if (i > m_currentFloor)
            break;
        else
            target.Draw(m_floors[i].second->getRenderResult(transparent));
    }
    m_LesChanged = false;
}

void Tower::addFloor(Level &floor)
{
    m_floors.push_back(Floor(getNextFloorDefaultName(), levelPtr(&floor)));
}

void Tower::addFloor(const std::string &floorpath)
{
    Level *floor = new Level(true);
    if (LevelFileInterpreter::readLevel(*floor, floorpath))
        m_floors.push_back(Floor(getNextFloorDefaultName(), levelPtr(floor)));
}

std::string Tower::getNextFloorDefaultName()
{
    std::string temp;
    const std::string size= gv.nbToText(m_floors.size());
    if (m_floors.size() < 10)
        temp += '0';
    return temp + size;
}
