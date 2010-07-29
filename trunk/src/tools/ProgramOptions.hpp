#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>

const char INI_PREFIXED_ACCESS = '/';
const std::string INI_PREFIX_FORBIDDEN(&INI_PREFIXED_ACCESS);

template <typename ReturnTypeT, typename ClassT>
struct ConvertMethod
{
    typedef ReturnTypeT (ClassT::*t_pointer)(const std::string&);

    ConvertMethod(const t_pointer &function, const ClassT &instance)
        : pointer(function), instance(instance)
    { }

    ReturnTypeT operator()(const std::string &toConvert) const
    {
        return (instance.*pointer)(toConvert);
    }

    private:
        const t_pointer &pointer;
        const ClassT &instance;
};

struct Value
{
    template <typename TypeT>
    Value(const std::string &value, const TypeT &defaultValue,
        const bool keyExists) : m_value(value), m_keyExists(keyExists)
    {
        std::ostringstream oss;
        oss << defaultValue;
        m_defaultValue = oss.str();
    }

    bool toBool() const;
    int toInt() const;
    std::string toString() const
    {
        if (!m_value.empty())
            return m_value;
         return m_defaultValue;
    }

    template <typename TypeT>
    TypeT toPersonalType(TypeT (*converter)(const std::string&)) const
    {
        return converter(m_value);
    }
    template <typename TypeT, typename ClassT>
    TypeT toPersonalType(const ConvertMethod<TypeT, ClassT> &converter) const
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

class OptionsReader
{
    public:
        OptionsReader();
        ~OptionsReader();

        template <typename TypeT> Value value(const std::string &key,
            const TypeT &defaultValue = std::string(""),
            const bool &includePrefix = true) const
        {
            std::string toFind;
            if (includePrefix)
                toFind = prefix;
            toFind += key;
            const option_cIter iter = findOptionFromNameConst(toFind);
            if (iter != options.end())
                return Value(iter->value, defaultValue, true);
            return Value("", defaultValue, false);
        }

        bool parseIniFile(const std::string &filename, const bool &useTree = true);
        bool parseCommandLine(const unsigned int &argc, char *argv[]);
        void addOption(const Option &option, const bool &removeSpaces = true,
            const bool &replaceIfExisting = true);

        void beginGroup(const std::string &name)
        {
            const std::string toAdd(clearPrefix(name));
            if (!toAdd.empty())
                prefix += toAdd + INI_PREFIXED_ACCESS;
        }
        void endGroup()
        {
            if (prefix.empty())
                return;
            if (prefix.size() <= 1)
            {
                prefix.clear();
                return;
            }
            boost::algorithm::trim_right_if(prefix, boost::algorithm::is_any_of(
                INI_PREFIX_FORBIDDEN));
            const std::string::size_type pos = prefix.find_last_of(INI_PREFIXED_ACCESS);
            if (pos != prefix.npos)
                prefix.erase(pos+1, prefix.npos);
            else
                prefix.clear();
        }
        std::string currentPrefix() const { return prefix; }

        static bool stringToBool(const std::string &text);

    private:
        inline static std::string clearPrefix(const std::string &string)
        {
           std::string temp = string;
            for (unsigned int i = 0; i < INI_PREFIX_FORBIDDEN.size(); i++)
                boost::algorithm::erase_all(temp, &INI_PREFIX_FORBIDDEN[i]);
            return temp;
        }
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

        std::list<Option> options;
        std::string prefix;
};

struct OptionsSaver
{
    OptionsSaver() { }
    virtual ~OptionsSaver() { }

    virtual void openFile(const std::string &filename) = 0;
    virtual void closeFile() = 0;

    virtual void beginGroup(const std::string &group) = 0;
    virtual void endGroup() = 0;
};

class OptionsSaverIni : public OptionsSaver
{
    public:
        OptionsSaverIni() : mainPrefixWritten(false) { }
        ~OptionsSaverIni();

        void openFile(const std::string &filename);
        void closeFile();

        void beginGroup(const std::string &group);
        void endGroup();

    private:
        std::ifstream file;
        std::string prefix;
        bool mainPrefixWritten;
};

#endif /* PROGRAMOPTIONS_HPP */
