#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
extern "C"
{
    #include <time.h> // Warning => C code
}
#include "Engine.hpp"
#include "tools/FilesLoader.hpp"
#include "gui/ErrorScreens.hpp"
#include "constantes.hpp"

using namespace std;

void setVerticalSync(const string &text, bool &vsync)
{
    unsigned int number = 0;
    istringstream iss(text);
        iss >> number;
    if (number == 0 || number == 1)
    {
        vsync = number;
        cout << "Vertical synchronization set to : " << vsync << "\n";
    }
}

void setLimitFps(const string &limit, unsigned int &fps)
{
    int number = 0;
    istringstream iss(limit);
        iss >> number;
    if (number < 0)
    {
        cerr << "Error : " << number << " is negative.\n";
        return;
    }

    fps = number;
    if (number == 0)
        cout << "Limit fps disabled\n";
    else
        cout << "Limit fps set to " << number << "\n";
}

void setModules(const string &list, vector<string> &modules)
{
    string temp(list);
    if (temp.empty())
        return;
    if (temp[temp.size()-1] != ';')
        temp += ';';
    cout << "Modules : ";
    string module;
    for (unsigned int i = 0; i < temp.size(); i++)
    {
        char letter = temp[i];
        if (letter == ';' && !module.empty())
        {
            char lastLetter = module[module.size()-1];
            if (lastLetter != '\\' && lastLetter != '/')
                module += '/';
            modules.push_back(module);
            cout << module << " ";
            module.clear();
        }
        else
            module += letter;
    }
    cout << "\n";
}

void interpretArguments(const unsigned int &argc, char *argv[], bool &vsync,
                        unsigned int &limitfps, vector<string> &modules)
{
    if (argc <= 1)
    {
        cout << "  No arguments.\n";
        return;
    }
    cout << "\n";
    for (unsigned int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        cout << "- Argument " << i << " : \"" << arg << "\"\n\t";
        if (arg== "-d")
        {
            cout << "Debug mode enabled by defaut.\n";
            gv.debugMode = true;
        }
        else if (arg.substr(0, 6) == "-vsync")
            setVerticalSync(arg.substr(7, arg.size()), vsync);
        else if (arg.substr(0, 9) == "-limitfps")
            setLimitFps(arg.substr(10, arg.size()), limitfps);
        else if (arg.substr(0, 5) =="-mods")
            setModules(arg.substr(6, arg.size()), modules);
        else
            cout << "Error : unknow argument\n";
    }
}

void printRunningTime(const sf::Clock &clock)
{
    unsigned int runningTime = static_cast<unsigned int>(clock.GetElapsedTime());
    unsigned int minutes = runningTime / 60;
    unsigned int  seconds = runningTime % 60;
    cout << minutes << " minute(s), " << seconds << " second(s)";
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

    bool vsync = true;
    unsigned int limitfps = 60;
    vector<string> modules;
        modules.push_back(baseModule);
    cout << "\nInterpreting arguments...\n";
    interpretArguments(argc, argv, vsync, limitfps, modules);
    //gv.options.loadOptions(argc, argv, vsync, limitfps, modules);
    cout << "\n";

    sf::RenderWindow window(sf::VideoMode(gv.SCREEN_W, gv.SCREEN_H, 32),
                            gv.windowTitle, sf::Style::Close);

    if (!FilesLoader::loadModules(modules))
    {
        ErrorScreens::missingResources(window);
        cout << "Game will now exit.\n";
        cout.rdbuf(oldBuf);
        cerr.rdbuf(oldBuf2);
        return EXIT_FAILURE;
    }

    cout << "\nInitializing game engine.\n";
    Engine engine(window, vsync, limitfps);
    cout << "Launching game engine.\n";
    engine.run();

    cout << "\n--- End of the program [";
    printRunningTime(clock);
    cout << "] ---";

    // End of redirecting
    cout.rdbuf(oldBuf);
    cerr.rdbuf(oldBuf2);

    return EXIT_SUCCESS;
}
