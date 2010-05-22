#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include "Level.hpp"
#include "tools/FilesLoader.hpp"

//typedef std::pair<std::string, levelPtr> Floor;
struct Floor
{
    Floor(const std::string &path, const std::string &alias) : alias(alias)/*,
        data(true)
    { data.setFilename(path); }*/{}
    std::string filename, alias;
    //Level data;
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
        Tower();
        ~Tower();

        void render(sf::RenderTarget &target);
        void addFloor(Level &floor);
        void addFloor(const std::string &name, const std::string &alias = "");
        void addLesElement(const LesElement &nLesElement);
        void setCurrentFloor(const unsigned int &currentFloor) {
            m_currentFloor = currentFloor; }
        void setStairsDescriptionFlag(const char &flag) {
            m_stairsDescriptionFlag = flag; }
        void loadFloors();

        Level *getCurrentFloor() { /*return m_floors[m_currentFloor].second.get(); */ return NULL; }

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
        bool m_LesChanged;
};

#endif /* TOWER_HPP */
