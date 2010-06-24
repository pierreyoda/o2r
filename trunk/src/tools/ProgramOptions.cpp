#include <iostream>
#include <sstream>
#include "ProgramOptions.hpp"
#include "../constantes.hpp"

using namespace std;

const string NEW_ARG_STRING = "-";
const char EGUALS_SYMBOL = '=';
const char SEPARATION_SYMBOL = ';';
const bool STRICT_PARSING = false;

ProgramOptions::ProgramOptions()
{

}

ProgramOptions::~ProgramOptions()
{

}

int ProgramOptions::valueInt(const string &key, const int &defaultValue) const
{
    int value = defaultValue;
    unsigned int argId = getArgIdFromName(key);
    if (argId < args.size() && !args[argId].value.empty())
    {
        istringstream iss(args[argId].value);
        iss >> value;
    }
    return value;
}

bool ProgramOptions::valueBool(const string &key, const bool &defaultValue) const
{
    bool value = defaultValue;
    unsigned int argId = getArgIdFromName(key);
    if (argId < args.size())
    {
        try
        {
            value = stringToBool(args[argId].value);
        }
        catch (const string &error)
        {
            cout << "\t" << error << "\n";
        }
    }
    return value;
}

string ProgramOptions::valueString(const string &key, const string &defaultValue) const
{
    string value = defaultValue;
    unsigned int argId = getArgIdFromName(key);
    if (argId < args.size())
        value = args[argId].value;
    return value;
}

void ProgramOptions::valueVector(vector<string> &vector, const string &key,
                                 const bool areDirs)
{
    unsigned int argId = getArgIdFromName(key);
    if (argId >= args.size())
        return;
    string value = args[argId].value;
    if (value.empty())
        return;
    if (value[value.size()-1] != ';')
        value += ';';
    string temp;
    for (unsigned int i = 0; i < value.size(); i++)
    {
        char letter = value[i];
        if (letter == ';' && !temp.empty())
        {
            if (areDirs)
            {
                char lastLetter = temp[temp.size()-1];
                if (lastLetter != '\\' && lastLetter != '/')
                    temp += '/';
            }
            vector.push_back(temp);
            temp.clear();
        }
        else
            temp += letter;
    }
}

bool ProgramOptions::parseCommandLine(const unsigned int &argc, char *argv[])
{
    for (unsigned int i = 1; i < argc; i++)
    {
        try
        {
            args.push_back(parseArgument(argv[i]));
            cout << "\t- Argument " << i;
            if (i < 10)
                cout << " ";
            cout <<  " : " << argv[i] << "\n";
        }
        catch (const string &error)
        {
            cout << "\t" << error << "\n";
        }
    }
    return true;
}

Argument ProgramOptions::parseArgument(const string &argument) const
{
    string parsingError("Error parsing argument '" + argument + "' : unknown format."),
        name, value;
    bool a = true;
    if (argument.size() <= NEW_ARG_STRING.size())
        throw parsingError;
    string temp = argument;
    if (argument.substr(0, NEW_ARG_STRING.size()) != NEW_ARG_STRING)
    {
        string message = "missing '" + NEW_ARG_STRING + "' at the begin of '"
                    + argument + "'.";
        if (STRICT_PARSING)
            throw "Error : " + message;
        else
            cout << "\t" << "Warning : " << message << "\n";
        a = false;
    }
    else
        temp = argument.substr(NEW_ARG_STRING.size(), argument.size());

    string::size_type egualsPos = argument.find(EGUALS_SYMBOL);
    if (egualsPos == string::npos)
        return Argument(temp, "");
    if (egualsPos >= temp.size())
        throw parsingError;
    if (!a)
        ++egualsPos;
    name = temp.substr(0, egualsPos-1), value = temp.substr(egualsPos, temp.size());

    return Argument(name, value);
}

bool ProgramOptions::stringToBool(const string &text) const
{
    if (text == "0" || text == "false")
        return false;
    else if (text == "1" || text == "true" || text.empty())
        return true;
    throw "Error : '" + text + "' is not a boolean.";
}

unsigned int ProgramOptions::getArgIdFromName(const string &name) const
{
    for (unsigned int i = 0; i < args.size(); i++)
        if (name == args[i].name)
            return i;
    return args.size();
}
