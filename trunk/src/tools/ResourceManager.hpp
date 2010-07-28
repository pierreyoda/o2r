/**
MIT License:

Copyright (c) 2008 Adam W. Brown (www.darkrockstudios.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

/* Modified by pierreyoda (Pierre-Yves Diallo) - 2010 */

#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <string>
#include <map>
#include "FilesPathHandler.hpp"

template <class T>
class ResourceManager
{
    public:
        typedef std::pair<std::string, T*> Resource;
        typedef std::map<std::string, T*>  ResourceMap;

    private:
        ResourceMap m_resource;

        T* find (const std::string &strId)
        {
            T* resource = 0;
            typename ResourceMap::iterator it = m_resource.find(strId);
            if (it != m_resource.end())
                resource = it->second;
            return resource;
        }

    protected:
        virtual T* load(const std::string &strId) = 0;

    public:
        ResourceManager() { }

        virtual ~ResourceManager()
        {
            releaseAllResources();
        }

        T* getResource(const std::string &strId, const bool &isAlias = true)
        {
            std::string file = gFph(strId);
            if (!isAlias || file.empty())
                file = strId;
            T* resource = find(file);
            if (resource == 0)
            {
                resource = load(file);
                if (resource != 0)
                    m_resource.insert(Resource(file, resource));
            }
            return resource;
        }

    void releaseResource(const std::string &strId)
    {
        T *resource = find(strId);
        if (resource != 0)
        {
            delete resource;
            m_resource.erase(m_resource.find(strId));
        }
    }

    void releaseAllResources()
    {
        while (m_resource.begin() != m_resource.end())
        {
            delete m_resource.begin()->second;
            m_resource.erase(m_resource.begin());
        }
    }
};

#endif /* RESOURCEMANAGER_H_INCLUDED */
