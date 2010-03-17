#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <vector>
#include <string>
//#include <boost/program_options.hpp>

class ProgramOptions
{
    public:
        ProgramOptions();
        ~ProgramOptions();

        bool loadOptions(const int &argc, char *argv[], bool &vsync,
                            unsigned int &limitfps, std::vector<std::string> &modules);

    private:
        //boost::program_options::options_description desc;
};

#endif /* PROGRAMOPTIONS_HPP */
