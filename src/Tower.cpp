#include "Tower.hpp"
#include "tools/ShaderManager.hpp"

// TODO (Pierre-Yves#4#): [EFFET VISUEL] Ajouter flou progressif + changement de teinte (effet profondeur verticale < ==shaders)
// TODO (Pierre-Yves#5#): [EFFET VISUEL] Ajouter une option pour désactiver les shaders
Tower::Tower() : m_lowerFloorsShader(*gShaderManager.getResource("blur.sfx")),
    m_lowerFloorsShader2(*gShaderManager.getResource("colorize.sfx")),
    m_currentFloor(0), m_stairsDescriptionFlag(stairsDescriptionDefaultFlag),
    m_LesChanged(true)
{
    temp.Create(gv.SCREEN_W, gv.SCREEN_H);
    temp2.Create(gv.SCREEN_W, gv.SCREEN_H);
    previousFloorsRender.Create(gv.SCREEN_W, gv.SCREEN_H);
    previousFloorsRenderResult.SetImage(previousFloorsRender.GetImage());
}

Tower::~Tower()
{
    m_floors.clear();
}

void Tower::render(sf::RenderTarget &target)
{
    /*for (unsigned int i = 0; i < m_floors.size(); i++)
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
    m_LesChanged = false;*/
    //target.Draw(getPrevFloorsRenderResult(), m_lowerFloorsShader2);
    if (m_LesChanged)
    {
        //m_floors[m_currentFloor].second->updateCasesImages();
        m_LesChanged = false;
    }
    bool transparent = (m_currentFloor == 0);
    //target.Draw(m_floors[m_currentFloor].second->getRenderResult(transparent));
}

const sf::Sprite &Tower::getPrevFloorsRenderResult()
{
    /*static unsigned int prevCurrentFloor = 0;
    if (m_currentFloor != prevCurrentFloor)
    {
        previousFloorsRender.Clear();
        prevCurrentFloor = m_currentFloor;
        for (unsigned int i = 0; i < m_currentFloor; i++)
            previousFloorsRender.Draw(m_floors[i].second->getRenderResult(),
                                      m_lowerFloorsShader);
        previousFloorsRender.Display();
    }
    return previousFloorsRenderResult;*/
}

void Tower::addFloor(Level &floor)
{
    //m_floors.push_back(Floor(getNextFloorDefaultName(), levelPtr(&floor)));
}

void Tower::addFloor(const std::string &name, const std::string &alias)
{
    /*Level *floor = new Level(true);
    if (LevelFileInterpreter::readLevel(*floor, name))
        m_floors.push_back(Floor(getNextFloorDefaultName(), levelPtr(floor)));*/
    std::string levelAlias = alias;
    if (alias.empty())
        levelAlias = getNextFloorDefaultName();
    if (FilesLoader::fileExists(name))
        m_floors.push_back(Floor(name, levelAlias));
}

std::string Tower::getNextFloorDefaultName()
{
    std::string temp;
    const std::string size= gv.nbToText(m_floors.size());
    if (m_floors.size() < 10)
        temp += '0';
    return temp + size;
}
