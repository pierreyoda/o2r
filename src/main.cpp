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

void loadGlobalOptions(const OptionsReader &options)
{
    gv.debugMode = options.value("d", false).toBool();
    if (gv.debugMode)
        gLog << "Debug mode enabled.\n";
    gv.compatibilityMode = options.value("oldPC", false).toBool();
    if (gv.compatibilityMode)
        gLog << "Compatibility mode enabled : performances may be reduced.\n";
}

const vector<string> getModules(const std::string &value)
{
    vector<string> modules;
    modules.push_back(baseModule);

    string arg = value;
    if (arg.empty())
        return modules;
    if (arg[arg.size()-1] != ';')
        arg += ';';
    string temp;
    for (unsigned int i = 0; i < arg.size(); i++)
    {
        char letter = arg[i];
        if (letter == ';' && !temp.empty())
        {
            char lastLetter = temp[temp.size()-1];
            if (lastLetter != '\\' && lastLetter != '/')
                temp += '/';
            modules.push_back(temp);
            temp.clear();
        }
        else
            temp += letter;
    }

    return modules;
}

int main(int argc, char *argv[])
{
    if (!gLog.goodInit())
        gLog << "Logging error : cannot open file \"log.txt\"\n";
    sf::Clock clock;
    gLog << "--- Launch of the program ---\n";
    // Writing date
    time_t rawtime = time(0);
    gLog << "Launched on " << ctime(&rawtime);
    gLog << "Version : " << gameVersion << "\n";

    gLog.changeHierarchy(1);
    gLog << "\nInterpreting arguments...\n";
    OptionsReader options;
        options.parseCommandLine(argc, argv);

    gLog.useHierarchy(true);
    loadGlobalOptions(options);
    const bool vsync = options.value("vsync", true).toBool();
    if (!vsync)
        gLog << "V. sync disabled.\n";
    int limitfps = options.value("limitfps", 60).toInt();
    if (limitfps < 0)
        limitfps = 60;
    if (limitfps == 0)
        gLog << "FPS limit disabled.\n";
    else if (limitfps != 60)
        gLog << "FPS limit set to " << limitfps << ".\n";
    const vector<string> modules = options.value("mods", "")
        .toPersonalType(getModules);
    const bool le = options.value("LE", false).toBool();
    if (le)
        gLog << "Launcher edition used.\n";
    const string les = options.value("les", "").toString();
    gLog.useHierarchy(false);
    if (!les.empty())
        TowerFileInterpreter::readLes(les, gv.lesElements);
    gLog.changeHierarchy(0);
    gLog << "\n";

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
        const bool game = options.value("game", true).toBool(),
            adjustWindowSize = options.value("adjustWindowSize", false).toBool(),
            towerMode = options.value("towerMode", false).toBool();
        if (adjustWindowSize)
            gLog << "The window will expand to adjust to the level size when it is possible.\n";
        string level = options.value("level", "data/1.txt").toString();
        gLog << "\nInitializing engine.\n";
        LauncherEditionEngine engine(window, vsync, limitfps, adjustWindowSize);
        const int nbOfCats = options.value("nbOfCats", -1).toInt(),
            nbOfRW = options.value("nbOfRW", -1).toInt(),
            nbOfLives = options.value("nbOfLives", DEFAULT_NB_OF_LIVES).toInt();
        if (game)
        {
            if (nbOfLives >= 0)
                gv.mouseNbOfLives = nbOfLives;
            engine.runAsGame(level, nbOfCats, nbOfRW, towerMode);
        }
        else if (towerMode)
            gLog << "Error : cannot edit directly a Tower. Game will now exit.\n";
        else
        {
            const sf::Vector2i size(options.value("levelX", DLVL_X).toInt(),
                              options.value("levelY", DLVL_Y).toInt());
            const bool noWarningAtSave = options.value("noWarningAtSave", false)
                .toBool(), emptyLevel = options.value("emptyLevel", false)
                .toBool();
            engine.runAsEditor(level, emptyLevel, size, nbOfCats, nbOfRW,
                               noWarningAtSave);
        }
    }

    printEndProgram(clock.GetElapsedTime());

    return EXIT_SUCCESS;
}
