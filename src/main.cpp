#include <iostream>
#include <string>
extern "C"
{
    #include <time.h> // Warning => C code
}
#include "Engine.hpp"
#include "LauncherEditionEngine.hpp"
#include "TowerFileInterpreter.hpp"
#include "tools/FilesLoader.hpp"
#include "tools/ProgramOptions.hpp"
#include "tools/Logger.hpp"
#include "gui/ErrorScreens.hpp"
#include "constantes.hpp"

using namespace std;

void printRunningTime(const float &runningTime)
{
    unsigned int time = static_cast<unsigned int>(runningTime),
    minutes = time / 60, seconds = time % 60;
    gLog << minutes << " minute(s), " << seconds << " second(s)";
}

void printEndProgram(const float &runningTime)
{
    gLog << "\n--- End of the program [";
    printRunningTime(runningTime);
    gLog << "] ---";
}

int main(int argc, char *argv[])
{
    if (!gLog.goodInit())
        gLog << "Logging error : cannot open file \"log.txt\"\n";
    // Redirecting to log
    sf::Clock clock;
    //gLog << "--- Launch of the program ---\n";
    gLog << "--- Launch of the program ---\n";
    // Writing date
    time_t rawtime = time(NULL);
    gLog << "Launched on " << ctime(&rawtime);
    gLog << "Version : " << gameVersion << "\n"; //  Program version

    vector<string> modules;
        modules.push_back(baseModule);
    gLog.changeHierarchy(1);
    gLog << "\nInterpreting arguments...\n";
    ProgramOptions options;
        options.parseCommandLine(argc, argv);

    gLog.useHierarchy(true);
    gv.debugMode = options.valueBool("d", false);
    if (gv.debugMode)
        gLog << "Debug mode enabled.\n";
    const bool vsync = options.valueBool("vsync", true);
    if (!vsync)
        gLog << "V. sync disabled.\n";
    int limitfps = options.valueInt("limitfps", 60);
    if (limitfps < 0)
        limitfps = 60;
    if (limitfps == 0)
        gLog << "FPS limit disabled.\n";
    else if (limitfps != 60)
        gLog << "FPS limit set to " << limitfps << ".\n";
    options.valueVector(modules, "mods", true);
    bool le = options.valueBool("LE", false);
    if (le)
        gLog << "Launcher edition used.\n";
    gLog << "\n";
    const string les = options.valueString("les", "");
    if (!les.empty())
        TowerFileInterpreter::readLes(les, gv.lesElements);
    gLog.changeHierarchy(0);

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H, 32),
                            gv.windowTitle, sf::Style::Close);

    if (!FilesLoader::loadModules(modules))
    {
        ErrorScreens::missingResources(window);
        gLog << "Game will now exit.\n";
        printEndProgram(clock.GetElapsedTime());
        return EXIT_FAILURE;
    }

    if (!le)
    {
        gLog << "\nInitializing game engine.\n";
        Engine engine(window, vsync, limitfps);
        gLog << "Launching game engine.\n";
        engine.run();
    }
    else
    {
        const bool game = options.valueBool("game", true),
            adjustWindowSize = options.valueBool("adjustWindowSize", false);
        if (adjustWindowSize)
            gLog << "The window will expand to adjust to the level size when it is possible.\n";
        string level = options.valueString("level", "data/1.txt");
        gLog << "\nInitializing engine.\n";
        LauncherEditionEngine engine(window, vsync, limitfps, adjustWindowSize);
        const int nbOfCats = options.valueInt("nbOfCats", -1),
            nbOfRW = options.valueInt("nbOfRW", -1),
            nbOfLives = options.valueInt("nbOfLives", DEFAULT_NB_OF_LIVES);
        if (game)
        {
            if (nbOfLives >= 0)
                gv.mouseNbOfLives = nbOfLives;
            engine.runAsGame(level, nbOfCats, nbOfRW);
        }
        else
        {
            const sf::Vector2i size(options.valueInt("levelX", DLVL_X),
                              options.valueInt("levelY", DLVL_Y));
            const bool noWarningAtSave = options.valueBool("noWarningAtSave",
                false), emptyLevel = options.valueBool("emptyLevel", false);
            engine.runAsEditor(level, emptyLevel, size, nbOfCats, nbOfRW,
                               noWarningAtSave);
        }
    }


    printEndProgram(clock.GetElapsedTime());

    return EXIT_SUCCESS;
}
