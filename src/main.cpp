#include <iostream>
#include <string>
extern "C"
{
    #include <time.h> // Warning => C code
}
#include "Engine.hpp"
#include "LauncherEditionEngine.hpp"
#include "tools/FilesLoader.hpp"
#include "tools/ProgramOptions.hpp"
#include "gui/ErrorScreens.hpp"
#include "constantes.hpp"

using namespace std;

void printRunningTime(const float &runningTime)
{
    unsigned int time = static_cast<unsigned int>(runningTime),
    minutes = time / 60, seconds = time % 60;
    cout << minutes << " minute(s), " << seconds << " second(s)";
}

void printEndProgram(const float &runningTime)
{
    cout << "\n--- End of the program [";
    printRunningTime(runningTime);
    cout << "] ---";
}

int main(int argc, char *argv[])
{
    // Redirecting to log
    sf::Clock clock;
    ofstream out("log.txt");
    streambuf *oldBuf = cout.rdbuf(out.rdbuf());
    streambuf *oldBuf2 = cerr.rdbuf(out.rdbuf());
    cout << "--- Launch of the program ---\n";
    // Writing date
    time_t rawtime = time(NULL);
    cout << "Launched on " << ctime(&rawtime);
    cout << "Version : " << gameVersion << "\n"; //  Program version

    vector<string> modules;
        modules.push_back(baseModule);
    cout << "\nInterpreting arguments...\n";
    ProgramOptions options;
    options.parseCommandLine(argc, argv);
    gv.debugMode = options.valueBool("d", false);
    if (gv.debugMode)
        cout << "\tDebug mode enabled.\n";
    const bool vsync = options.valueBool("vsync", true);
    if (!vsync)
        cout << "\tV. sync disabled.\n";
    int limitfps = options.valueInt("limitfps", 60);
    if (limitfps < 0)
        limitfps = 60;
    if (limitfps == 0)
        cout << "\tFPS limit disabled.\n";
    else if (limitfps != 60)
        cout << "\tFPS limit set to " << limitfps << ".\n";
    options.valueVector(modules, "mods", true);
    bool le = options.valueBool("LE", false);
    if (le)
        cout << "\tLauncher edition used.\n";
    cout << "\n";

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H, 32),
                            gv.windowTitle, sf::Style::Close);

    if (!FilesLoader::loadModules(modules))
    {
        ErrorScreens::missingResources(window);
        cout << "Game will now exit.\n";
        printEndProgram(clock.GetElapsedTime());
        cout.rdbuf(oldBuf);
        cerr.rdbuf(oldBuf2);
        return EXIT_FAILURE;
    }

    if (!le)
    {
        cout << "\nInitializing game engine.\n";
        Engine engine(window, vsync, limitfps);
        cout << "Launching game engine.\n";
        engine.run();
    }
    else
    {
        const bool game = options.valueBool("game", true);
        string level = options.valueString("level", "data/1.txt");
        cout << "\nInitializing engine.\n";
        LauncherEditionEngine engine(window, vsync, limitfps);
        if (game)
        {
            const int nbOfCats = options.valueInt("nbOfCats", -1),
                nbOfRW = options.valueInt("nbOfRW", -1),
                nbOfLives = options.valueInt("nbOfLives", DEFAULT_NB_OF_LIVES);
            if (nbOfLives >= 0)
                gv.mouseNbOfLives = nbOfLives;
            engine.runAsGame(level, nbOfCats, nbOfRW);
        }
        else
        {
            const sf::Vector2i size(options.valueInt("levelX", DLVL_X),
                              options.valueInt("levelY", DLVL_Y));
            if (options.valueBool("emptyLevel", false))
                level = emptyLevelName;
            const bool noWarningAtSave = options.valueBool("noWarningAtSave",
                                                           false);
            engine.runAsEditor(level, size, noWarningAtSave);
        }
    }


    printEndProgram(clock.GetElapsedTime());

    // End of redirecting
    cout.rdbuf(oldBuf);
    cerr.rdbuf(oldBuf2);

    return EXIT_SUCCESS;
}
