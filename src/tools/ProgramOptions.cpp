#include <iostream>
#include <sstream>
#include "ProgramOptions.hpp"
#include "../GlobalVariables.hpp"
#include "Logger.hpp"

using namespace std;

const string NEW_ARG_STRING = "-";
const char EGUALS_SYMBOL = '=';
const bool STRICT_PARSING = false;

ProgramOptions::ProgramOptions()
{

}

ProgramOptions::~ProgramOptions()
{

}

int Value::toInt() const
{
    if (m_value.empty() && m_defaultValue.empty())
        return 0;
    int value;
    if (m_value.empty())
        value = gv.textToNb(m_defaultValue);
    else
        value = gv.textToNb(m_value);
    return value;
}

bool stringToBoolShort(const string &text)
{
    bool value = false;
    try
    {
        value = ProgramOptions::stringToBool(text);
    }
    catch (const string &error)
    {
        gLog << logH << error << "\n";
    }
    return value;
}

bool Value::toBool() const
{
    bool value = false;
    if (!m_keyExists)
        value = stringToBoolShort(m_defaultValue);
    else
        value = stringToBoolShort(m_value);
    return value;
}

bool ProgramOptions::parseCommandLine(const unsigned int &argc, char *argv[])
{
    gLog.useHierarchy(false);
    for (unsigned int i = 1; i < argc; i++)
    {
        gLog << logH << "- ";
        try
        {
            args.push_back(parseArgument(argv[i]));
            gLog << "Argument " << i;
            if (i < 10)
                gLog << " ";
            gLog <<  " : " << argv[i] << "\n";
        }
        catch (const string &error)
        {
            gLog << error << "\n";
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
            gLog << "Warning : " << message << "\n" << logH << "->";
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

bool ProgramOptions::stringToBool(const string &text)
{
    if (text == "0" || text == "false")
        return false;
    else if (text == "1" || text == "true" || text.empty())
        return true;
    throw "Error : '" + text + "' is not a boolean.";
}

const arg_cIter ProgramOptions::findArgFromName(const string &name) const
{
    return find(args.begin(), args.end(), name);
}
