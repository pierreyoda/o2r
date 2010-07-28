#include <iostream>
#include "TowerFileInterpreter.hpp"
#include "tools/ProgramOptions.hpp"
#include "tools/FilesLoader.hpp"
#include "tools/Logger.hpp"

using namespace std;

bool TowerFileInterpreter::readTower(Tower &tower, const string &filename)
{
    gLog << "Reading tower '" << filename << "'.\n";
    gLog.changeHierarchy(1, true);
    TiXmlDocument file(filename.c_str());
    if (!file.LoadFile())
    {
        gLog << "Error while loading tower from '" << filename << "' (Error #"
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
        gLog << "Error : main node is not 'Tower'.\n";
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
            bool ok = true;
            string filename = "", alias = "";
            if (elem->Attribute("ref") == 0)
            {
                gLog << logH << "Error : missing attribute 'ref'.\n";
                ok = false;
            }
            else
                filename = basedir + elem->Attribute("ref");
            if (elem->Attribute("name") != 0)
                alias = elem->Attribute("name");
            if (ok && !FilesLoader::fileExists(filename))
                gLog << logH << "Error : level file '" << filename << "' does not exist.\n";
            else if (ok)
                tower.addFloor(filename, alias);
        }
        else if (nodeName == "LES")
            readLes(elem, gv.lesElements);
        else if (nodeName == "stairs")
            readStairs(elem, tower);
        else
            gLog << logH << "Warning : unrecognized node '" << nodeName << "'.\n";
        elem = elem->NextSiblingElement();
    }
    gLog.changeHierarchy(-1, true);

    return true;
}

bool TowerFileInterpreter::readStairs(TiXmlElement *elem, Tower &tower)
{
    TiXmlAttribute *attrib = elem->FirstAttribute();
    while (attrib)
    {
        const string attribName = attrib->Name();
        const string attribValueStr = attrib->Value();
        if (attribName == "ref")
            return readStairs(attribValueStr, tower);
        else if (attribName == "persoflag")
        {
            if (!attribValueStr.empty())
                tower.setStairsDescriptionFlag(attribValueStr[0]);
        }
        attrib = attrib->Next();
    }

    elem = elem->FirstChildElement("staircase");
    while (elem)
    {
        string from, to;
        bool final = false;
        TiXmlAttribute *attrib = elem->FirstAttribute();
        while (attrib)
        {
            if (attrib->Name() == 0)
                continue;
            const string attribName = attrib->Name();
            if (attrib->Value() == 0)
                continue;
            const string attribValueStr = attrib->Value();
            if (!attribValueStr.empty())
            {
                if (attribName == "from")
                    from = attribValueStr;
                else if (attribName == "to")
                    to = attribValueStr;
                else if (attribName == "final")
                    final = OptionsReader::stringToBool(attribValueStr);
            }
            attrib = attrib->Next();
        }
        bool add = true;
        if (from.empty())
        {
            gLog << logH << "[Tower] Stairs error : no source specified.\n";
            add = false;
        }
        if (!final && to.empty())
        {
            gLog << logH << "[Tower] Stairs error : no destination specified.\n";
            add = false;
        }
        if (add)
            tower.addStairs(from, to);
        elem = elem->NextSiblingElement("staircase");
    }

    return true;
}

bool TowerFileInterpreter::readStairs(const string &filename, Tower &tower)
{
    gLog << "\tReading stairs '" << filename << "'.\n";
    TiXmlDocument file(filename.c_str());
    if (!file.LoadFile())
    {
        gLog << "Error while loading stairs from '" << filename << "' (Error #"
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
        gLog << logH << "Error : main node is not 'stairs'.\n";
        return false;
    }
    return readStairs(elem, tower);
}

bool TowerFileInterpreter::readLes(TiXmlElement *elem, l_LesElement &lesElements)
{
    string basedir = "";
    if (elem->Attribute("basedir") != 0)
        basedir = elem->Attribute("basedir");
    if (!basedir.empty())
    {
        const char lastLetter = basedir[basedir.size()-1];
        if (lastLetter != '\\' && lastLetter != '/')
            basedir += '/';
    }

    elem = elem->FirstChildElement("element");
    while (elem)
    {
        CASETYPE type = NOTHING;
        char character = '0';
        string imgpath = "nothing.png";
        TiXmlAttribute *attrib = elem->FirstAttribute();
        bool fromBaseDir = false;
        while (attrib)
        {
            if (attrib->Name() == 0)
                continue;
            const string attribName = attrib->Name();
            if (attrib->Value() == 0)
                continue;
            const string attribValueStr = attrib->Value();
            if (attribName == "char" && attribValueStr.size() >= 1)
                character = attribValueStr[0];
            else if (attribName == "img")
                imgpath = attribValueStr;
            else if (attribName == "type")
                type = Level::stringToCasetype(attribValueStr);
            else if (attribName == "fromBaseDir")
                fromBaseDir = OptionsReader::stringToBool(attribValueStr);
            attrib = attrib->Next();
        }
        bool ok = true;
        if (imgpath.empty() || imgpath == baseModule)
        {
            gLog << logH << "Error : no image specified.\n";
            ok = false;
        }
        /*else if (!FilesLoader::fileExists(imgpath))
            gLog << logH << "Warning : image '" << imgpath << "' not found.\n";*/
        if (ok)
            lesElements.push_back(LesElement(character, type, imgpath));
        elem = elem->NextSiblingElement("element");
    }
    return true;
}

bool TowerFileInterpreter::readLes(const string &filename, l_LesElement &lesElements,
                                   const bool &clearPreviousLes)
{
    gLog << logH << "Reading LES description file '" << filename << "'.\n";
    gLog.changeHierarchy(1, true);
    if (clearPreviousLes)
        lesElements.clear();
    TiXmlDocument file(filename.c_str());
    if (!file.LoadFile())
    {
        gLog << logH << "Error while loading LES from '" << filename << "' (Error #"
            << file.ErrorId() << " : " << file.ErrorDesc() << ")\n";
        return false;
    }

    TiXmlHandle hdl(&file);
    TiXmlElement *elem = hdl.FirstChildElement().Element();
    if (!elem)
        return false;
    string nodeName = elem->Value();
    if (nodeName != "LES")
    {
        gLog << "Error : main node is not 'LES'.\n";
        return false;
    }
    return readLes(elem, lesElements);
}
