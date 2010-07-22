#ifndef FILESPATHHANDLER_HPP
#define FILESPATHHANDLER_HPP

#include <map>
#include <string>
#include "Logger.hpp"

typedef std::map<const std::string, std::string> map_filesPath;

class FilesPathHandler
{
    public:
        FilesPathHandler() { }
        ~FilesPathHandler() { }

        void addFile(const std::string &alias, const std::string &path,
            const bool &replace = true)
        {
            map_filesPath::iterator iter = find(alias);
            if (iter == filespath.end())
                filespath.insert(make_pair(alias, path));
            else if (replace)
                iter->second = path;
        }

        std::string getFilepath(const std::string &alias) const
        {
            return operator()(alias);
        }
        std::string operator()(const std::string &alias) const
        {
            const map_filesPath::const_iterator iter = find(alias);
            if (iter != filespath.end())
                return iter->second;
            gLog << logH << "Error : cannot found '" << alias << "'.";
            return "";
        }

    private:
        inline map_filesPath::iterator find(const std::string &alias)
        {
            return filespath.find(alias);
        }
        inline map_filesPath::const_iterator find(const std::string &alias) const
        {
            return filespath.find(alias);
        }

        map_filesPath filespath;
};

extern FilesPathHandler gFph;

#endif /* FILESPATHHANDLER_HPP */
