#include "Tower.hpp"
#include "TowerFileInterpreter.hpp"

std::string Tower::shader1 = std::string(), Tower::shader2 = std::string();

// TODO (Pierre-Yves#4#): [EFFET VISUEL] Ajouter flou progressif + changement de teinte (effet profondeur verticale < ==shaders)
// TODO (Pierre-Yves#5#): [EFFET VISUEL] Ajouter une option pour désactiver les shaders
Tower::Tower(const std::string &file) : m_currentFloor(0),
    m_stairsDescriptionFlag(stairsDescriptionDefaultFlag)
{
    if (shader1.empty())
        shader1 = gFph("blur.sfx");
    if (shader2.empty())
        shader2 = gFph("colorize.sfx");
    if (!m_lowerFloorsShader.LoadFromFile(shader1))
        gLog << "Error : cannot load shader blur from '" << shader1 << "'.\n";
    if (!m_lowerFloorsShader.LoadFromFile(shader2))
        gLog << "Error : cannot load shader blur from '" << shader2 << "'.\n";
    if (!gv.compatibilityMode)
    {
        temp.Create(SCREEN_W, SCREEN_H);
        temp2.Create(SCREEN_W, SCREEN_H);
        previousFloorsRender.Create(SCREEN_W, SCREEN_H);
        previousFloorsRenderResult.SetImage(previousFloorsRender.GetImage());
    }
    TowerFileInterpreter::readTower(*this, file);
    if (m_floors.empty())
        return;
    m_floors[0].loadLevel();
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
        if (!m_floors[i].loaded())
            m_floors[i].loadLevel();
        if (m_floors[i].data.get() == 0)
            continue;
        if (i == 0)
            transparent = false;
        if (i < m_currentFloor)
        {
            if (!gv.compatibilityMode)
            {
                const sf::Image &img  = *m_floors[i].data->getRenderResult(transparent).GetImage();
                    temp.Clear();
                    temp.Draw(sf::Sprite(img), m_lowerFloorsShader);
                    temp2.Clear();
                    temp2.Draw(sf::Sprite(temp.GetImage()), m_lowerFloorsShader2);
                target.Draw(sf::Sprite(temp2.GetImage()));
            }
            else
            ; // to be continued...
        }
        else if (i > m_currentFloor)
            break;
        else
            target.Draw(m_floors[i].data->getRenderResult(transparent));
    }
    target.Draw(getPrevFloorsRenderResult(), m_lowerFloorsShader2);
    bool transparent = (m_currentFloor == 0);
    target.Draw(m_floors[m_currentFloor].data->getRenderResult(transparent));
}

const sf::Sprite &Tower::getPrevFloorsRenderResult()
{
    static unsigned int prevCurrentFloor = 0;
    if (m_currentFloor != prevCurrentFloor)
    {
        previousFloorsRender.Clear();
        prevCurrentFloor = m_currentFloor;
        for (unsigned int i = 0; i < m_currentFloor; i++)
        {
            if (m_floors[i].data != 0)
                previousFloorsRender.Draw(m_floors[i].data->getRenderResult(),
                                      m_lowerFloorsShader);
        }
        previousFloorsRender.Display();
    }
    return previousFloorsRenderResult;
}

void Tower::addFloor(const std::string &name, const std::string &alias)
{
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
