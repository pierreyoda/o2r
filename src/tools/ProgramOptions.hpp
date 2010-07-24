#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/trim.hpp>

template <typename T, typename U>
struct ConvertMethod
{
    typedef T (U::*t_pointer)(const std::string&);

    ConvertMethod(const t_pointer &function, const U &instance)
        : pointer(function), instance(instance)
    { }

    T operator()(const std::string &toConvert) const
    {
        return (instance.*pointer)(toConvert);
    }

    private:
        const t_pointer &pointer;
        const U &instance;
};

struct Value
{
    template <typename T> Value(const std::string &value, const T &defaultValue,
        const bool keyExists) : m_value(value), m_keyExists(keyExists)
    {
        std::ostringstream oss;
        oss << defaultValue;
        m_defaultValue = oss.str();
    }

    bool toBool() const;
    int toInt() const;
    std::string toString() const { return m_value; }

    template <typename T>
    T toPersonalType(T (*converter)(const std::string&)) const
    {
        return converter(m_value);
    }
    template <typename T, typename U>
    T toPersonalType(const ConvertMethod<T, U> &converter) const
    {
        return converter(m_value);
    }

    private:
        std::string m_value, m_defaultValue;
        const bool m_keyExists;
};

struct Option
{
    Option(const std::string &name, const std::string &value) : name(name),
        value(value) { }

    inline bool operator==(const std::string &key) const
    {
        return (name == key);
    }

    std::string name, value;
};

typedef std::list<Option>::iterator option_iter;
typedef std::list<Option>::const_iterator option_cIter;

class ProgramOptions
{
    public:
        ProgramOptions();
        ~ProgramOptions();

        template <typename T> Value value(const std::string &key,
            const T &defaultValue = std::string("")) const
        {
            const option_cIter iter = findOptionFromNameConst(key);
            if (iter != options.end())
                return Value(iter->value, defaultValue, true);
            return Value("", defaultValue, false);
        }

        bool parseIniFile(const std::string &filename, const bool &useTree = true);
        bool parseCommandLine(const unsigned int &argc, char *argv[]);

        static bool stringToBool(const std::string &text);

    private:
        inline static std::string removeExtraSpaces(std::string &string)
        {
            boost::algorithm::trim(string);
            return string;
        }
        inline static bool containsOnlySpaces(const std::string &string)
        {
            for (unsigned int i = 0; i < string.size(); i++)
                if (string[i] != ' ' && string[i] != '\t')
                    return false;
            return true;
        }
        inline option_iter findOptionFromName(const std::string &name)
        {
            return std::find(options.begin(), options.end(), name);
        }
        inline const option_cIter findOptionFromNameConst(const std::string &name)
            const
        {
            return std::find(options.begin(), options.end(), name);
        }
        Option parseArgument(const std::string &argument) const;
        Option parseOptionLine(const std::string &line) const;
        void addOption(const Option &option, const bool &removeSpaces = true,
            const bool &replaceIfExisting = true);

        std::list<Option> options;
        std::string prefix;
};

#endif /* PROGRAMOPTIONS_HPP */
