#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include "GlobalVariables.hpp"
#include "Object.hpp"

// Level case
struct LevelCase
{
    LevelCase(const sf::Vector2i &cpos, const char &character);

    void updateImage();

    char character;
    CASETYPE type;
    Object drawable;
};

// Level informations (more convenient than a boost::tuple)
struct LevelInformations
{
    sf::Vector2i size, mouseStartPos;
    std::string filename, name;
    unsigned int iCatsNb, catsNb, randomWallsNb;
    bool hasChanged;
};

// Level
class Level
{
    public:
        Level(const std::string &file = emptyLevelName,
            const std::string &name = "", const sf::Vector2i &sizeIfEmpty
                = sf::Vector2i(DLVL_X, DLVL_Y),
            const int &persoNbOfCats = -1, const int &persoNbOfRW = -1);
        ~Level();

        const sf::Sprite &getRenderResult(const bool &transparent = false);
        void renderToOtherTarget(sf::RenderTarget &target,
                                 const bool &transparent = false);

        bool writeLevel(const std::string &filename);
        void randomWalls();
        void updateCasesImages();
        void mustRedraw() { infos.hasChanged = true; }

        void setMouseStartPos(const sf::Vector2i &pos)
        {
            if (!Object::outOfScreen(pos, infos.size))
                infos.mouseStartPos = pos;
        }
        void setNbOfRandomWalls(const unsigned int &wallnb)
        {
            if (wallnb >= 0 && wallnb < (unsigned int)infos.size.x*infos.size.y)
                infos.randomWallsNb = wallnb;
        }

        LevelInformations &getInfosRef() { return infos; }
        const LevelInformations &getInfos() const { return infos; }
        void setCaseType(const sf::Vector2i &pos, const CASETYPE &type);
        void setCaseType(const sf::Vector2i &pos, const char &character);
        CASETYPE getCaseType(const sf::Vector2i &pos) const;
        CASETYPE getCaseType(const unsigned int &x, const unsigned int &y) const;
        unsigned int nbOfCasetype(const CASETYPE &casetype) const;

        static char casetypeToChar(const CASETYPE &type);
        static CASETYPE charToCasetype(const char &caracter);
        static CASETYPE stringToCasetype(const std::string &word);
        static sf::Image *charToImage(const char &character);

    private:
        void fillWithNothingType();
        bool readLevelFile();
            bool analyseLevelFileLine(const std::string &line,
                        const unsigned int &linenb, const sf::Vector2i &oldSize,
                        unsigned int &gap);
            bool setSizeFromLine(const std::string &line, const sf::Vector2i &oldSize);
            void setiNbOfCatsFromText(const std::string &text);
            void setNbOfRandomWallsFromText(const std::string &text);
        void render(const bool &transparent, sf::RenderTarget *otherTarget = 0);
        void renderDrawable(sf::RenderTarget *target, const sf::Vector2i &pos);
        bool noCaseThere(const sf::Vector2i &pos);

        sf::RenderImage renderTarget;
        sf::Sprite renderResult;
        std::vector< std::vector<LevelCase> > cases;
        LevelInformations infos;
};

typedef boost::shared_ptr<Level> levelPtr;

#endif /* LEVEL_HPP */
