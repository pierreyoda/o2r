#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include "Level.hpp"
#include "tools/FilesLoader.hpp"

struct Floor
{
    Floor(const std::string &path, const std::string &alias) : filename(path),
        alias(alias), m_loaded(false)
    {

    }
    ~Floor()
    {
        if (data.unique())
            data.reset();
    }
    void loadLevel(const bool &reloadIfLoaded = false)
    {
        if (m_loaded && !reloadIfLoaded)
            return;
        data.reset(new Level(filename, alias));
        m_loaded = true;
    }

    std::string filename, alias;
    levelPtr data;

    bool loaded() const { return m_loaded; }

    private:
        bool m_loaded;
};

struct StairsDescriptionElement
{
    char sourceChar, destChar;
    std::string sourceLevel, destLevel;
};

typedef std::list<StairsDescriptionElement> l_stairsDescription;

class Tower
{
    public:
        Tower(const std::string &file);
        ~Tower();

        void render(sf::RenderTarget &target);
        void addFloor(const std::string &name, const std::string &alias = "");
        void addStairs(const std::string &source, const std::string &dest);
        void setStairsDescriptionFlag(const char &flag) {
            m_stairsDescriptionFlag = flag; }

        levelPtr getCurrentFloor()
        {
            if (m_floors.empty() || m_currentFloor >= m_floors.size())
                return levelPtr();
            return m_floors[m_currentFloor].data;
        }

    private:
        std::string getNextFloorDefaultName();
        const sf::Sprite &getPrevFloorsRenderResult();

        sf::RenderImage temp, temp2, previousFloorsRender;
        sf::Sprite previousFloorsRenderResult;
        std::vector<Floor> m_floors;
        l_stairsDescription m_stairs;
        sf::Shader m_lowerFloorsShader, m_lowerFloorsShader2;
        unsigned int m_currentFloor;
        char m_stairsDescriptionFlag;
        std::string shader1, shader2;
};

#endif /* TOWER_HPP */
