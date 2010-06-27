#include <iostream>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include "FilesLoader.hpp"
#include "ImageManager.hpp"
#include "ShaderManager.hpp"
#include "Logger.hpp"

using namespace std;
namespace fs = boost::filesystem;

// TODO (Pierre-Yves#3#): [GESTION FICHIER] R��crire gestion des 'alias' (sortir des XXX-Manager) et des managers de ressources
bool FilesLoader::loadModules(const vector<string> &modules,
                  const bool &recursive, const bool &modulesOnlyKnownFiles)
{
    sf::Clock clock;

    if (modules.empty())
    {
        gLog << "Fatal error : no modules specified.\n";
        return false;
    }
    gLog << "Finding base files... ";
    const string baseDir = modules[0];
    fileList baseFiles;
    if (!findPresentFiles(baseFiles, baseDir))
    {
        gLog << "Fatal error : cannot find base files.\n";
        return false;
    }
    gLog << "Loading base files...\n";
    if (!loadFiles(baseFiles, baseDir, baseFiles, true))
    {
        gLog << "Fatal error : cannot load base files.\n";
        return false;
    }

    gLog << "\tFinding module(s) files... ";
    if (modules.size() <= 1)
    {
        gLog << "No module(s) specified : skipping step.\n";
        gLog << "Preloading time : " << clock.GetElapsedTime() << "s\n";
        return true;
    }
    gLog << "\n";
    fileList moduleFiles, alreadyLoaded;
    gLog.changeHierarchy(0);
    for (unsigned int i = 1; i < modules.size(); i++)
    {
        moduleFiles.clear();
        string moduledir = modules[i];
        if (moduledir != baseDir)
        {
            bool isAlreadyLoaded = false;
            gLog << "\t- Module : " << moduledir << " -\n";
            for (unsigned int i = 0; i < alreadyLoaded.size(); i++)
            {
                if (moduledir == alreadyLoaded[i])
                {
                    isAlreadyLoaded = true;
                    gLog << "Warning : module already loaded : skipping step.\n";
                    break;
                }
            }
            if (isAlreadyLoaded)
                continue;
            else if (!findPresentFiles(moduleFiles, moduledir))
                continue;
            else if (!loadFiles(moduleFiles, moduledir, baseFiles))
                gLog << "\tError : failed to load module '" << moduledir << "'.\n";
            else
                alreadyLoaded.push_back(moduledir);
        }
    }
    gLog << "Preloading time : " << clock.GetElapsedTime() << "s\n";

    return true;
}

bool FilesLoader::loadFiles(const fileList &files, const string &dir,
    const fileList &baseFiles, const bool checkIfAlreadyLoaded,
    const bool &basemodule)
{
    gLog.changeHierarchy(1);
    fileList alreadyLoaded;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        gLog.useHierarchy(true);
        string file = dir + files[i];
        gLog << file;
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
        gLog << "\n";
    }
    gLog.changeHierarchy(1);
    gLog.useHierarchy(false);
    return true;
}

bool FilesLoader::loadFile(const string &filepath)
{
    gLog.useHierarchy(false);
    const fs::path file(filepath);
    if (filepath.empty() ||  !fs::exists(file))
        return false;
    string extension(file.extension());
    extension = extension.substr(1, extension.size());
    if (extension == "bmp" || extension == "png" || extension == "jpg" ||
        extension == "tga" || extension == "dds" || extension == "psd")
    {
        //gLog << " (Image)";
        return (gImageManager.getResource(file.filename(), filepath,
                                          true) != NULL);
    }
    else if (extension == "sfx")
    {
        gLog << " (Shader)";
        return (gShaderManager.getResource(file.filename(), filepath,
                                           true) != NULL);
    }
    else
    {
        gLog << " Warning : non supported format. Skipping file...";
        return true;
    }
    gLog.useHierarchy(true);
}

bool FilesLoader::findDefinedFiles(fileList &files, const string &imgdir)
{
    static const string resourcesList = "data/resources.txt";
    ifstream file(resourcesList.c_str(), ios::in);
    if (!file)
    {
        gLog << "Error : file \"" << resourcesList << "\" is not present.\n";
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
        gLog << "Error : folder '" << imgdir << "' does not exist.\n";
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
