#include <iostream>
#include "TowerFileInterpreter.hpp"
#include "tools/FilesLoader.hpp"

using namespace std;

/*bool TowerFileInterpreter::readTower(Tower &tower, const string &filename)
{
    cout << "Reading tower '" << filename << "'.\n";
    TiXmlDocument file(filename.c_str());
    if (!file.LoadFile())
    {
        cerr << "Error while loading tower from '" << filename << "' (Error #"
            << file.ErrorId() << " : " << file.ErrorDesc() << ")\n";
        return false;
    }

    TiXmlHandle hdl(&file);
    TiXmlElement *elem = hdl.FirstChildElement().Element();
    if (!elem)
        return false;
    string nodeName = elem->Value();
    if (nodeName != "Tower")
    {
        cerr << "Error : main node is not 'Tower'.\n";
        return false;
    }
    string basedir = elem->Attribute("basedir");
    char lastLetter = basedir[basedir.size()-1];
    if (lastLetter != '\\' && lastLetter != '/')
        basedir += '/';

    gv.lesElements.clear();
    elem = elem->FirstChildElement();
    while (elem)
    {
        nodeName = elem->Value();
        if (nodeName == "floor")
        {
            Level *level = new Level(true);
            const string filename = basedir + elem->Attribute("ref");
            level->setFilename(filename);
            cout << "\t";
            if (!FilesLoader::fileExists(filename))
                cerr << "Error : level file '" << filename << "' does not exist.\n";
            else if (LevelFileInterpreter::readLevel(*level, filename))
            //else
                tower.addFloor(*level);
        }
        else if (nodeName == "LES")
        {
            readLes(elem, gv.lesElements);
        }
        else if (nodeName == "stairs")
            readStairs(elem);
        else
            cout << "\tWarning : unrecognized node '" << nodeName << "'.\n";
        elem = elem->NextSiblingElement();
    }

    return true;
}

bool TowerFileInterpreter::readStairs(TiXmlElement *elem)
{
    TiXmlAttribute *attrib = elem->FirstAttribute();
    while (attrib)
    {
        const string attribName = attrib->Name();
        const string attribValueStr = attrib->Value();
        if (attribName == "ref")
            return readStairs(attribValueStr);
        else if (attribName == "basedir");
        else if (attribName == "persoflag");
        attrib = attrib->Next();
    }

    elem = elem->FirstChildElement("staircase");
    while (elem)
    {
        elem = elem->NextSiblingElement("staircase");
    }

    return true;
}

bool TowerFileInterpreter::readStairs(const string &filename)
{
    cout << "\tReading stairs '" << filename << "'.\n";
    TiXmlDocument file(filename.c_str());
    if (!file.LoadFile())
    {
        cerr << "Error while loading stairs from '" << filename << "' (Error #"
            << file.ErrorId() << " : " << file.ErrorDesc() << ")\n";
        return false;
    }

    TiXmlHandle hdl(&file);
    TiXmlElement *elem = hdl.FirstChildElement().Element();
    if (!elem)
        return false;
    string nodeName = elem->Value();
    if (nodeName != "stairs")
    {
        cerr << "Error : main node is not 'stairs'.\n";
        return false;
    }
    return readStairs(elem);
}

bool TowerFileInterpreter::readLes(TiXmlElement *elem, l_LesElement &lesElements)
{
    string basedir = elem->Attribute("basedir");
    char lastLetter = basedir[basedir.size()-1];
    if (lastLetter != '\\' && lastLetter != '/')
        basedir += '/';

    elem = elem->FirstChildElement("element");
    while (elem)
    {
        CASETYPE type = NOTHING;
        char character = '0';
        string imgpath = "nothing.png";
        TiXmlAttribute *attrib = elem->FirstAttribute();
        while (attrib)
        {
            const string attribName = attrib->Name();
            const string attribValueStr = attrib->Value();
            if (attribName == "char" && attribValueStr.size() >= 1)
                character = attribValueStr[0];
            else if (attribName == "img")
                imgpath = attribValueStr;
            else if (attribName == "type")
                type = Level::stringToCasetype(attribValueStr);
            else if (attribName == "fromBaseDir" && attribValueStr == "1")
            {
                string temp =  baseModule;
                imgpath = temp + imgpath;
            }
            attrib = attrib->Next();
        }
        bool ok = true;
        if (imgpath.empty() || imgpath == baseModule)
        {
            cerr << "Error : no image specified.\n";
            ok = false;
        }
        else if (!FilesLoader::fileExists(imgpath))
        {
            cerr << "Error : image '" << imgpath << "'does not exist.\n";
            ok = false;
        }
        if (ok)
            lesElements.push_back(LesElement(character, type, imgpath));
        elem = elem->NextSiblingElement("element");
    }
    return true;
}

bool TowerFileInterpreter::readLes(const string &filename, l_LesElement &lesElements)
{
    return true;
}*/
