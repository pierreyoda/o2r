#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <list>
#include <string>

template <typename T, typename U>
struct ValueConvertMemberFunction
{
    typedef T (U::*t_pointer)(const std::string&);

    ValueConvertMemberFunction(const t_pointer &function, const U &instance)
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
    T toPersonalType(const ValueConvertMemberFunction<T, U> &converter) const
    {
        return converter(m_value);
    }

    private:
        std::string m_value, m_defaultValue;
        const bool m_keyExists;
};

struct Argument
{
    Argument(const std::string &name, const std::string &value) : name(name),
        value(value) { }

    inline bool operator==(const std::string &key) const { return (name == key); }

    std::string name, value;
};

typedef std::list<Argument>::const_iterator arg_cIter;

class ProgramOptions
{
    public:
        ProgramOptions();
        ~ProgramOptions();

        template <typename T> Value value(const std::string &key,
            const T &defaultValue = std::string("")) const
        {
            const arg_cIter iter = findArgFromName(key);
            if (iter != args.end())
                return Value(iter->value, defaultValue, true);
            return Value("", defaultValue, false);
        }

        bool parseCommandLine(const unsigned int &argc, char *argv[]);

        static bool stringToBool(const std::string &text);

    private:
        const arg_cIter findArgFromName(const std::string &name) const;
        Argument parseArgument(const std::string &argument) const;

        std::list<Argument> args;
};

#endif /* PROGRAMOPTIONS_HPP */
