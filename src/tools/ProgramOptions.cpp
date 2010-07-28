#include <iostream>
#include <sstream>
#include "ProgramOptions.hpp"
#include "../GlobalVariables.hpp"
#include "Logger.hpp"

using namespace std;

const string NEW_ARG_STRING = "-";
const char EGUALS_SYMBOL = '=', INI_COMMENT_SYMBOL = ';', INI_PREFIX_OPEN = '[',
    INI_PREFIX_CLOSE = ']';
const bool STRICT_CL_PARSING = false, STRICT_INI_PARSING = false;

OptionsReader::OptionsReader()
{

}

OptionsReader::~OptionsReader()
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

bool Value::toBool() const
{
    bool value = false;
    if (!m_keyExists)
        value = OptionsReader::stringToBool(m_defaultValue);
    else
        value = OptionsReader::stringToBool(m_value);
    return value;
}

bool OptionsReader::parseIniFile(const string &filename, const bool &useTree)
{
    ifstream file(filename.c_str(), ios::in);
    if (!file)
        return false;

    string line;
    prefix.clear();
    while (getline(file, line))
    {
        const string parsingError("Error parsing line '" + line
            + "' : invalid format.");
        const string::size_type prefixOpenPos = line.find(INI_PREFIX_OPEN);
        if (useTree && prefixOpenPos != string::npos)
        {
            if (prefixOpenPos >= line.size())
            {
                gLog << logH << parsingError << "\n";
                continue;
            }
            string::size_type prefixClosePos = line.find(INI_PREFIX_CLOSE);
            if (prefixClosePos == string::npos)
            {
                string message("missing '");
                message.push_back(INI_PREFIX_CLOSE);
                message  += "' at the end of '" + line + "'.";
                if (STRICT_INI_PARSING)
                {
                    gLog << logH << "Error : " + message;
                    continue;
                }
                gLog << logH << "Warning : " << message << "\n";
                prefixClosePos = line.size();
            }
            if (prefixClosePos-prefixOpenPos >= line.size())
            {
                gLog << logH << parsingError << "\n";
                continue;
            }
            prefix = line.substr(prefixOpenPos+1, prefixClosePos-1)
                + INI_PREFIXED_ACCESS;
            continue;
        }
        const string::size_type commentPos = line.find(INI_COMMENT_SYMBOL);
        if (commentPos != string::npos)
        {
            if (commentPos >= line.size())
                continue;
            line = line.substr(0, commentPos);
        }
        if (containsOnlySpaces(line))
            continue;
        addOption(parseOptionLine(prefix + line));
    }

    file.close();
    prefix.clear();

    return true;
}

bool OptionsReader::parseCommandLine(const unsigned int &argc, char *argv[])
{
    gLog.useHierarchy(false);
    for (unsigned int i = 1; i < argc; i++)
    {
        gLog << logH << "- ";
        try
        {
            const Option arg = parseArgument(argv[i]);
            addOption(arg);
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
    return true;
}

Option OptionsReader::parseArgument(const string &argument) const
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

Option OptionsReader::parseOptionLine(const string &line) const
{
    string parsingError("Error parsing line '" + line
        + "' : unknown format."), name(""), value("");

    const string::size_type egualsPos = line.find(EGUALS_SYMBOL);
    if (egualsPos == string::npos)
        return Option(line, "");
    if (egualsPos >= line.size())
        throw parsingError;
    name = line.substr(0, egualsPos),
    value = line.substr(egualsPos+1, line.size());

    return Option(name, value);
}

void OptionsReader::addOption(const Option &option, const bool &removeSpaces,
    const bool &replaceIfExisting)
{
    string name = option.name, value = option.value;
    if (removeSpaces)
        removeExtraSpaces(name), removeExtraSpaces(value);
    if (replaceIfExisting)
    {
        const option_iter iter = findOptionFromName(name);
        if (iter != options.end())
        {
            iter->value = value;
            return;
        }
    }
    options.push_back(Option(name, value));
}

bool OptionsReader::stringToBool(const string &text)
{
    if (text == "0" || text == "false")
        return false;
    else if (text == "1" || text == "true" || text.empty())
        return true;
    gLog << "Error : '" + text + "' is not a boolean.";
    return false;
}
