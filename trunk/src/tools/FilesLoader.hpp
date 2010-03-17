#ifndef FILESLOADER_HPP
#define FILESLOADER_HPP

#include <vector>
#include <string>
#include <boost/filesystem.hpp>

typedef std::vector<std::string> fileList;

class FilesLoader
{
    public:
        FilesLoader() { }

        static bool loadModules(const std::vector<std::string> &modules,
            const bool &recursive = false, const bool &modulesOnlyKnownFiles = true);
        static bool fileExists(const std::string &filename);

    private:
        static bool loadFiles(const fileList &files, const std::string &dir,
            const fileList &baseFiles, const bool checkIfAlreadyLoaded = true,
            const bool &basemodule = false);
        static bool loadFile(const std::string &filepath);
        static bool findDefinedFiles(fileList &files, const std::string &imgdir);
        static bool findPresentFiles(fileList &files, const std::string &imgdir, const bool &recursive = false);
};

#endif /* FILESLOADER_HPP */
