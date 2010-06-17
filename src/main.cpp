#include <iostream>
#include <string>
extern "C"
{
    #include <time.h> // Warning => C code
}
#include "Engine.hpp"
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
        cout << "\t- Debug mode enabled.\n";
    bool vsync = options.valueBool("vsync", true);
    if (!vsync)
        cout << "\t- V. sync disabled.\n";
    int limitfps = options.valueInt("limitfps", 60);
    if (limitfps < 0)
        limitfps = 60;
    if (limitfps == 0)
        cout << "\t- FPS limit disabled.\n";
    else if (limitfps != 60)
        cout << "\t- FPS limit set to " << limitfps << ".\n";
    options.valueVector(modules, "mods", true);
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

    cout << "\nInitializing game engine.\n";
    Engine engine(window, vsync, limitfps);
    cout << "Launching game engine.\n";
    engine.run();

    printEndProgram(clock.GetElapsedTime());

    // End of redirecting
    cout.rdbuf(oldBuf);
    cerr.rdbuf(oldBuf2);

    return EXIT_SUCCESS;
}
