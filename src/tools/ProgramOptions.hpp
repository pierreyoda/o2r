#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <vector>
#include <string>

struct Argument
{
    Argument(const std::string &name, const std::string &value) : name(name),
        value(value) { }

    std::string name, value;
};

class ProgramOptions
{
    public:
        ProgramOptions();
        ~ProgramOptions();

        int valueInt(const std::string &key, const int &defaultValue) const;
        bool valueBool(const std::string &key, const bool &defaultValue) const;
        std::string valueString(const std::string &key, const std::string &defaultValue) const;
        void valueVector(std::vector<std::string> &vector, const std::string &key,
                         const bool areDirs = false);

        bool parseCommandLine(const unsigned int &argc, char *argv[]);

    private:
        bool stringToBool(const std::string &text) const;
        unsigned int getArgIdFromName(const std::string &name) const;
        Argument parseArgument(const std::string &argument) const;

        std::vector<Argument> args;
};

#endif /* PROGRAMOPTIONS_HPP */
