#include <iostream>
#include "ProgramOptions.hpp"
#include "../constantes.hpp"

using namespace std;
//namespace po = boost::program_options;

ProgramOptions::ProgramOptions() //: desc("Allowed options")
{
    /*desc.add_options()
    ("help", "Produce help message for command line")
    ("d", "Enable by default debug mode (can be changed by pressing F12)")
    ("mods", po::value< vector<string> >(), "Custom modules to load")
    ("vsync", po::value<bool>(), "Enable (1) or disable (0) vertical synchronisation (default=1)")
    ("limitfps", po::value<unsigned int>(), "Change the fps limit (0=disabled ; default=60)")
    ;*/
}

ProgramOptions::~ProgramOptions()
{

}

bool ProgramOptions::loadOptions(const int &argc, char *argv[], bool &vsync,
                                 unsigned int &limitfps, vector<string> &modules)
{
    /*po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        cout << desc << "\n";
        return true;
    }
    if (vm.count("d"))
    {
        gv.debugMode = true;
        cout << "\tDebug mode enabled by defaut.\n";
    }
    if (vm.count("vsync"))
    {
        vsync = vm["vsync"].as<bool>();
        cout << "\t";
        if (vsync)
            cout << "Vertical synchronisation enabled\n";
        else
            cout << "Vertical synchronisation disabled\n";
    }
    if (vm.count("limitfps"))
    {
        limitfps = vm["limitfps"].as<unsigned int>();
        cout << "\t";
        if (limitfps == 0)
            cout << "Fps limit disabled";
        else
            cout << "Fps limit set to " << limitfps << "\n";
    }
    if (vm.count("mods"))
    {
        modules = vm["mods"].as< vector<string> >();
        cout << "\tModules set to :";
        for (unsigned int i = 0; i < modules.size(); i++)
            cout << modules[i] << " ";
        cout << "\n";
    }
    cout << "\n";
*/
    return false;
}
