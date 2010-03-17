#include <iostream>
#include <fstream>
#include <SFML/System.hpp>
#include "ImagesLoader.hpp"
#include "ImageManager.hpp"

using namespace std;

bool ImagesLoader::loadImages(const string &dir)
 {
    sf::Clock clock;
    cout << "Preloading files from " << dir << "... ";
    fileList files;
    if (!findDefinedFiles(files, dir))
        return false;
    fileList alreadyLoaded;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        string file = dir + files[i];
        for (unsigned int i = 0; i < alreadyLoaded.size(); i++)
            if (file == alreadyLoaded[i])
                continue;
        if (file.empty() || gImageManager.getResource(file) == NULL)
            return false;
        alreadyLoaded.push_back(file);
    }
    cout << "Preloading time : " << clock.GetElapsedTime() << "s" << endl;

    return true;
 }

bool ImagesLoader::findDefinedFiles(fileList &files, const string &dir)
{
    static const string resourcesList = "data/resources.txt";
    ifstream file(resourcesList.c_str(), ios::in);
    if (!file)
    {
        cerr << "Error : file \"" << resourcesList << "\" is not present."
                << endl;
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
