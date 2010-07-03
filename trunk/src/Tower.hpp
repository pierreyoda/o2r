#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include "Level.hpp"
#include "tools/FilesLoader.hpp"

struct Floor
{
    Floor(const std::string &path, const std::string &alias) : alias(alias)
    {
        data = NULL;
    }
    ~Floor()
    {
        delete data;
    }

    std::string filename, alias;
    Level *data;
};

struct StairsDescriptionElement
{
    std::string fromStairsName, toStairsName;
    sf::Vector2i fromStairsPos, toStairsPos;
};

typedef std::list<StairsDescriptionElement> l_stairsDescription;

class Tower
{
    public:
        Tower(const std::string &file);
        ~Tower();

        void render(sf::RenderTarget &target);
        void addFloor(const std::string &name, const std::string &alias = "");
        void setStairsDescriptionFlag(const char &flag) {
            m_stairsDescriptionFlag = flag; }

        Level *getCurrentFloor()
        {
            if (m_floors.empty() || m_currentFloor >= m_floors.size())
                return NULL;
            return m_floors[m_currentFloor].data;
        }

    private:
        std::string getNextFloorDefaultName();
        const sf::Sprite &getPrevFloorsRenderResult();

        sf::RenderImage temp, temp2, previousFloorsRender;
        sf::Sprite previousFloorsRenderResult;
        std::vector<Floor>  m_floors;
        l_stairsDescription m_stairs;
        sf::Shader &m_lowerFloorsShader, &m_lowerFloorsShader2;
        unsigned int m_currentFloor;
        char m_stairsDescriptionFlag;
};

#endif /* TOWER_HPP */
