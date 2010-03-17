#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h> // Warning => C code
#include "Engine.hpp"
#include "tools/ImagesLoader.hpp"
#include "gui/ErrorScreens.hpp"
#include "constantes.hpp"

using namespace std;

const string TITLE("Open Rodent's Revenge");

void setVerticalSync(const string &text, bool &vsync)
{
    unsigned int number = 0;
    istringstream iss(text);
        iss >> number;
    if (number == 0 || number == 1)
    {
        vsync = number;
        cout << "Vertical synchronization set to : " << vsync << endl;
    }
}

void setLimitFps(const string &limit, unsigned int &fps)
{
    int number = 0;
    istringstream iss(limit);
        iss >> number;
    if (number < 0)
    {
        cerr << "Error : " << number << " is negative." << endl;
        return;
    }

    fps = number;
    if (number == 0)
        cout << "Limit fps disabled" << endl;
    else
        cout << "Limit fps set to " << number << endl;
}

void setNbOfCats(const string &nb)
{
    int number = 0;
    istringstream iss(nb);
        iss >> number;
    if (number < 0)
    {
        cerr << "Error : " << number << " is negative." << endl;
        return;
    }
    gv.nbOfCats = number;
    cout << "Number of cats set to : " << number << endl;
}

void setTheme(const string &path)
{
    string theme = path;
    if (theme.empty())
        return;
    gv.currentTheme = theme;
    cout << "Theme set to : " << theme << endl;
}

void interpretArguments(const unsigned int &argc, char *argv[], bool &vsync,
                        unsigned int &limitfps)
{
    if (argc <= 1)
    {
        cout << "  No arguments." << endl;
        return;
    }
    cout << endl;
    for (unsigned int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        cout << "- Argument " << i << " : \"" << arg << "\"" << endl << "\t";
        if (arg== "-d")
        {
            cout << "Debug mode enabled by defaut." << endl;
            gv.debugMode = true;
        }
        else if (arg.substr(0, 9) == "-nbofcats")
            setNbOfCats(arg.substr(10, arg.size()));
        else if (arg.substr(0, 6) == "-vsync")
            setVerticalSync(arg.substr(7, arg.size()), vsync);
        else if (arg.substr(0, 9) == "-limitfps")
            setLimitFps(arg.substr(10, arg.size()), limitfps);
        else if (arg.substr(0, 5) =="theme")
            setTheme(arg.substr(6, arg.size()));
        else
            cout << "Error : unknow argument" << endl;
    }
}

int main(int argc, char *argv[])
{
    // Redirecting to log
    ofstream out("log.txt");
    streambuf* oldBuf = cout.rdbuf(out.rdbuf());
    streambuf* oldBuf2 = cerr.rdbuf(out.rdbuf());
    // Writing date
    time_t rawtime = time(NULL);
    cout << "Launched on " << ctime(&rawtime) << endl;

    cout << "Interpreting arguments...";
    bool vsync = true;
    unsigned int limitfps = 60;
    interpretArguments(argc, argv, vsync, limitfps);

    sf::RenderWindow window(sf::VideoMode(gv.SCREEN_W, gv.SCREEN_H, 32), TITLE,
                            sf::Style::Close);
        if (!ImagesLoader::loadImages(gv.currentTheme))
        {
            bool ok = true;
            if (gv.currentTheme == defaultTheme)
                ok = false;
            else
            {
                gv.currentTheme = defaultTheme;
                ok = ImagesLoader::loadImages(defaultTheme);
            }
            if (!ok)
            {
                ErrorScreens::missingResources(window);
                cout << "Game will now exit" << endl;
                return EXIT_FAILURE;
            }
        }

    std::cout << std::endl;
    cout << "Loading game engine." << endl;
    Engine engine(window, vsync, limitfps);
    cout << "Entering game's main loop." << endl;
    engine.run();
    cout << "End of the program." << endl;

    cout.rdbuf(oldBuf); // End of redirecting
    cerr.rdbuf(oldBuf2); // End of redirecting

    return EXIT_SUCCESS;
}
