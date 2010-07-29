#include <boost/algorithm/string.hpp>
#include "Tower.hpp"
#include "TowerFileInterpreter.hpp"

// TODO (Pierre-Yves#4#): [EFFET VISUEL] Ajouter flou progressif + changement de teinte (effet profondeur verticale < ==shaders)
// TODO (Pierre-Yves#5#): [EFFET VISUEL] Ajouter une option pour désactiver les shaders
Tower::Tower(const std::string &file) : m_currentFloor(0),
    m_stairsDescriptionFlag(stairsDescriptionDefaultFlag)
{
    shader1 = gFph("blur.sfx"), shader2 = gFph("colorize.sfx");
    if (!m_lowerFloorsShader.LoadFromFile(shader1))
        gLog << logH << "[Tower] Error : cannot load shader 1 from '"
            << shader1 << "'.\n";
    if (!m_lowerFloorsShader2.LoadFromFile(shader2))
        gLog << logH << "[Tower] Error : cannot load shader 2 from '"
            << shader2 << "'.\n";
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
                m_floors[i].data->renderToOtherTarget(target, transparent);
        }
        else if (i > m_currentFloor)
            break;
        else if (gv.compatibilityMode)
            m_floors[i].data->renderToOtherTarget(target, transparent);
        else
            target.Draw(m_floors[i].data->getRenderResult(transparent));
    }
    if (!gv.compatibilityMode)
    {
        target.Draw(getPrevFloorsRenderResult(), m_lowerFloorsShader2);
        bool transparent = (m_currentFloor == 0);
        target.Draw(m_floors[m_currentFloor].data->getRenderResult(transparent));
    }
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

void Tower::addStairs(const std::string &source, const std::string &dest)
{
    if (source.empty() || dest.empty())
        return;
    StairsDescriptionElement stair;
    std::vector<std::string> result;
    // Sources informations
    boost::algorithm::split(result, source,
        boost::algorithm::is_any_of(&m_stairsDescriptionFlag));
    if (result.size() < 2 || result[0].empty() || result[1].empty())
        return;
    stair.sourceLevel = result[0];
    stair.sourceChar = result[1][0];
    result.clear();
    // Destination informations
    boost::algorithm::split(result, dest,
        boost::algorithm::is_any_of(&m_stairsDescriptionFlag));
    if (result.size() < 2 || result[0].empty() || result[1].empty())
        return;
    stair.destLevel = result[0];
    stair.destChar = result[1][0];
    // Adding stairs
    m_stairs.push_back(stair);
}

/* From a level name and a case position, if there is stairs there will return
the other side position (which can be 'from' or 'dest') */
sf::Vector2i Tower::getStairsDestination(const sf::Vector2i &pos,
    const std::string &levelName)
{
    // To be implemented
}
