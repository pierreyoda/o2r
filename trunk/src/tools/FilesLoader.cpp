#include <iostream>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include "FilesLoader.hpp"
#include "ImageManager.hpp"
#include "ShaderManager.hpp"

using namespace std;
namespace fs = boost::filesystem;

bool FilesLoader::loadModules(const vector<string> &modules,
                  const bool &recursive, const bool &modulesOnlyKnownFiles)
{
    sf::Clock clock;

    if (modules.empty())
    {
        cerr << "Fatal error : no modules specified.\n";
        return false;
    }
    cout << "Finding base files... ";
    const string baseDir = modules[0];
    fileList baseFiles;
    if (!findPresentFiles(baseFiles, baseDir))
    {
        cerr << "Fatal error : cannot find base files.\n";
        return false;
    }
    cout << "Loading base files...\n";
    if (!loadFiles(baseFiles, baseDir, baseFiles, true))
    {
        cerr << "Fatal error : cannot load base files.\n";
        return false;
    }

    cout << "Finding module(s) files... ";
    if (modules.size() <= 1)
    {
        cout << "No module(s) specified : skipping step.\n";
        return true;
    }
    cout << "\n";
    fileList moduleFiles, alreadyLoaded;
    for (unsigned int i = 1; i < modules.size(); i++)
    {
        moduleFiles.clear();
        string moduledir = modules[i];
        if (moduledir != baseDir)
        {
            bool isAlreadyLoaded = false;
            cout << "\t- Module : " << moduledir << " -\n";
            for (unsigned int i = 0; i < alreadyLoaded.size(); i++)
            {
                if (moduledir == alreadyLoaded[i])
                {
                    isAlreadyLoaded = true;
                    cout << "\tWarning : module already loaded : skipping step.\n";
                    break;
                }
            }
            if (isAlreadyLoaded)
                continue;
            else if (!findPresentFiles(moduleFiles, moduledir))
                continue;
            else if (!loadFiles(moduleFiles, moduledir, baseFiles))
                cerr << "\tError : failed to load module '" << moduledir << "'.\n";
            else
                alreadyLoaded.push_back(moduledir);
        }
    }
    cout << "Preloading time : " << clock.GetElapsedTime() << "s\n";

    return true;
}

bool FilesLoader::loadFiles(const fileList &files, const string &dir,
    const fileList &baseFiles, const bool checkIfAlreadyLoaded,
    const bool &basemodule)
{
    fileList alreadyLoaded;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        string file = dir + files[i];
        cout << "\t" << file;
        if (checkIfAlreadyLoaded)
        {
            bool isAlreadyLoaded = false;
            for (unsigned int i = 0; i < alreadyLoaded.size(); i++)
            {
                if (file == alreadyLoaded[i])
                {
                    isAlreadyLoaded = true;
                    break;
                }
            }
            if (isAlreadyLoaded)
                continue;
        }
        if (!loadFile(file))
            return false;
        if (checkIfAlreadyLoaded)
            alreadyLoaded.push_back(file);
        cout << "\n";
    }
    return true;
}

bool FilesLoader::loadFile(const string &filepath)
{
    const fs::path file(filepath);
    if (filepath.empty() ||  !fs::exists(file))
        return false;
    string extension(file.extension());
    extension = extension.substr(1, extension.size());
    if (extension == "bmp" || extension == "png" || extension == "jpg" ||
        extension == "tga" || extension == "dds" || extension == "psd")
    {
        //cout << " (Image)";
        return (gImageManager.getResource(file.filename(), filepath,
                                          true) != NULL);
    }
    else if (extension == "sfx")
    {
        cout << " (Shader)";
        return (gShaderManager.getResource(file.filename(), filepath,
                                           true) != NULL);
    }
    else
    {
        cout << " Warning : non supported format. Skipping file...";
        return true;
    }
}

bool FilesLoader::findDefinedFiles(fileList &files, const string &imgdir)
{
    static const string resourcesList = "data/resources.txt";
    ifstream file(resourcesList.c_str(), ios::in);
    if (!file)
    {
        cerr << "Error : file \"" << resourcesList << "\" is not present.\n";
        return false;
    }
    string temp;
    while (!file.eof())
    {
        file >> temp;
        files.push_back(temp);
    }

    return true;
}

bool FilesLoader::findPresentFiles(fileList &files, const string &imgdir, const bool &recursive)
{
    const fs::path dir(imgdir);
    if (!fs::exists(dir))
    {
        cerr << "Error : folder '" << imgdir << "' does not exist.\n";
        return false;
    }

    fs::directory_iterator itEnd;
    for (fs::directory_iterator it(dir); it != itEnd; ++it)
	{
        if (recursive && fs::is_directory(it->status()))
        {
            if (!findPresentFiles(files, it->path().string()))
                return false;
        }
        else if (fs::is_regular(it->status()))
            files.push_back(it->filename());
	}
    return true;
}

bool FilesLoader::fileExists(const string &filename)
{
    return (fs::exists(filename));
}
