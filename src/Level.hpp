#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include "GlobalVariables.hpp"
#include "Object.hpp"

struct LevelCase
{
    LevelCase(const sf::Vector2i &cpos, const CASETYPE &ctype);

    void updateImage();

    char character;
    CASETYPE type;
    Object drawable;
};

// TODO (Pierre-Yves#3#): [OPTIMISATION] Ajouter gestion 'streaming' (possibilit� niveau vide � la construction pour lib�rer m�moire)
// TODO (Pierre-Yves#1#): [DECENTRALISATION] G�rer taille niveau dans 'Level'
class Level
{
    public:
        Level(const bool &empty = false);
        ~Level();

        const sf::Sprite &getRenderResult(const bool &transparent = false);

        void clearLevel();
        void resetLevel();
        void resizeLevel();
        void randomWalls();
        void updateCasesImages();
        void mustRedraw() { levelChanged = true; }

        void setMouseStartPos(const sf::Vector2i &pos)
        {
            if (!Object::outOfScreen(pos, size))
                mouseStartPos = pos;
        }
        void setSize(const sf::Vector2i &nsize)
        {
            if (nsize.x > 0 && nsize.y > 0)
                size = nsize;
        }
        void setNbOfRandomWalls(const unsigned int &wallnb)
        {
            if (wallnb >= 0 && wallnb < (unsigned int)size.x*size.y)
                randomWallsNb = wallnb;
        }
        void setNbOfCats(const unsigned &nb)
        {
            if (nb >= 0)
                catsNb = nb;
        }
        void setFilename(const std::string &nfilename)
        {
            filename = nfilename;
        }

        bool hasChanged() const { return levelChanged; }
        sf::Vector2i getMouseStartPos() const { return mouseStartPos; }
        sf::Vector2i getSize() const { return size; }
        sf::Vector2i &getSizeRef() { return size; }
        unsigned int getNbOfRandomWalls() { return randomWallsNb; }
        unsigned int getCatsNb() { return catsNb; }
        void setCaseType(const sf::Vector2i &pos, const CASETYPE &type);
        void setCaseType(const sf::Vector2i &pos, const char &character);
        CASETYPE getCaseType(const sf::Vector2i &pos) const;
        CASETYPE getCaseType(const unsigned int &x, const unsigned int &y) const;
        unsigned int nbOfCasetype(const CASETYPE &casetype) const;
        std::vector< std::vector<LevelCase> > &content() { return cases; }
        std::string getFilename() const { return filename; }

        static char casetypeToChar(const CASETYPE &type);
        static CASETYPE charToCasetype(const char &caracter);
        static CASETYPE stringToCasetype(const std::string &word);
        static sf::Image *charToImage(const char &character);

    private:
        void render(const bool &transparent);
        void renderDrawable(sf::RenderTarget &target, const sf::Vector2i &pos,
                            const CASETYPE &type);
        bool noCaseThere(const sf::Vector2i &pos);

        sf::RenderImage renderTarget;
        sf::Sprite renderResult;
        std::vector< std::vector<LevelCase> > cases;
        sf::Vector2i mouseStartPos, size;
        std::string filename;
        unsigned int randomWallsNb, catsNb;
        bool levelChanged;
};

typedef boost::shared_ptr<Level> levelPtr;

#endif /* LEVEL_HPP */
