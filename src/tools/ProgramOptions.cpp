#include <iostream>
#include <sstream>
#include "ProgramOptions.hpp"
#include "../GlobalVariables.hpp"
#include "Logger.hpp"

using namespace std;

const string NEW_ARG_STRING = "-";
const char EGUALS_SYMBOL = '=';
const bool STRICT_CL_PARSING = false, REPLACE_IF_EXISTING = false;

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
            const Option arg = parseArgument(argv[i]);
            args.push_back(arg);
            gLog << "Option " << i;
            if (i < 10)
                gLog << " ";
            gLog <<  " : " << arg.name << " ";
            if (!arg.value.empty())
                gLog << EGUALS_SYMBOL << " " << arg.value;
             gLog << "\n";
        }
        catch (const string &error)
        {
            gLog << error << "\n";
        }
    }
    parseArgument("-mod=true");
    return true;
}

Option ProgramOptions::parseArgument(const string &argument) const
{
    string parsingError("Error parsing argument '" + argument + "' : unknown format."),
        name, value;
    if (argument.size() <= NEW_ARG_STRING.size())
        throw parsingError;
    string temp = argument;
    if (argument.substr(0, NEW_ARG_STRING.size()) != NEW_ARG_STRING)
    {
        string message = "missing '" + NEW_ARG_STRING + "' at the begin of '"
                    + argument + "'.";
        if (STRICT_CL_PARSING)
            throw "Error : " + message;
        gLog << "Warning : " << message << "\n" << logH << "->";
    }
    else
        temp = argument.substr(NEW_ARG_STRING.size(), argument.size());

    return parseOptionLine(temp);
}

Option ProgramOptions::parseOptionLine(const string &line) const
{
    string parsingError("Error parsing line '" + line
        + "' : unknown format."), name(""), value("");

    string::size_type egualsPos = line.find(EGUALS_SYMBOL);
    if (egualsPos == string::npos)
        return Option(line, "");
    if (egualsPos >= line.size())
        throw parsingError;
    name = line.substr(0, egualsPos),
    value = line.substr(egualsPos+1, line.size());

    return Option(name, value);
}

bool ProgramOptions::stringToBool(const string &text)
{
    if (text == "0" || text == "false")
        return false;
    else if (text == "1" || text == "true" || text.empty())
        return true;
    throw "Error : '" + text + "' is not a boolean.";
}
