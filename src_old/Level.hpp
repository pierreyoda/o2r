#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "constantes.hpp"

enum CASETYPE
{
    NOTHING,
    BLOCK,
    WALL
};

class Level
{
    public:
        Level();
        ~Level();

        void render(sf::RenderTarget &target);

        void clearLevel();
        void resetLevel();
        void resizeLevel();
        void randomWalls();

        void setMouseStartPos(const sf::Vector2i &pos)
        {
            if (!Object::outOfScreen(pos))
                mouseStartPos = pos;
        }
        sf::Vector2i getMouseStartPos() const { return mouseStartPos; }
        void setNbOfRandomWalls(const unsigned int &wallnb)
        {
            if (wallnb >= 0 && wallnb < gv.LVL_X*gv.LVL_Y)
                randomWallsNb = wallnb;
        }
        unsigned int getNbOfRandomWalls() { return randomWallsNb; }
        void setCaseType(const sf::Vector2i &pos, const CASETYPE &type);
        CASETYPE getCaseType(const sf::Vector2i &pos) const;
        CASETYPE getCaseType(const unsigned int &x, const unsigned int &y) const;
        unsigned int nbOfCasetype(const CASETYPE &casetype) const;
        std::vector< std::vector<CASETYPE> > &content() { return cases; }

    private:
        void renderDrawable(sf::RenderTarget &target, const sf::Vector2i &pos,
                            const CASETYPE &type);

        std::vector< std::vector<CASETYPE> > cases;
        Object nothingDrawable, blockDrawable, wallDrawable;
        sf::Vector2i mouseStartPos;
        unsigned int randomWallsNb;
};

#endif /* LEVEL_HPP */
