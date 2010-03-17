#ifndef IMAGESLOADER_HPP
#define IMAGESLOADER_HPP

#include <vector>
#include <string>

typedef std::vector<std::string> fileList;

class ImagesLoader
{
    public:
        ImagesLoader() { }

        static bool loadImages(const std::string &dir);

    private:
        static bool findDefinedFiles(fileList &files, const std::string &dir);
};

#endif /* IMAGESLOADER_HPP */
