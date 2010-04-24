#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include "Level.hpp"

typedef std::pair<std::string, levelPtr> Floor;

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
        void addFloor(const std::string &level);
        void addLesElement(const LesElement &nLesElement);
        void setCurrentFloor(const unsigned int &currentFloor) {
            m_currentFloor = currentFloor; }
        void setStairsDescriptionFlag(const char &flag) {
            m_stairsDescriptionFlag = flag; }
        void loadFloors();

        Level *getCurrentFloor() { return m_floors[m_currentFloor].second.get(); }

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
