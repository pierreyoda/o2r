#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const std::string logH = "log::hierarchy_use"; // Log hierarchy string

class Logger
{
    public:
        Logger(const std::string &file = "log.txt");
        ~Logger();

        void log(const std::string &toLog, const bool &useHierarchy = false);
        void changeHierarchy(const unsigned int &nHierarchy,
            const bool &isOffset = false, const bool &use = false)
        {
            unsigned int hierarchy = nHierarchy;
            if (isOffset)
                hierarchy += m_hierarchy;
            if (hierarchy >= 0 && hierarchy < 10)
                m_hierarchy = hierarchy;
            useHierarchy(use);
        }

        bool goodInit() const { return m_goodInit; }
        void useHierarchy(const bool &use)
        {
            m_useHierarchy = use;
        }

        template <class T> Logger& operator <<(const T& toLog)
        {
            std::ostringstream oss;
            oss << toLog;
            const std::string string = oss.str();
            if (string == logH)
                m_useHierarchyNext = true;
            else
                log(string);
            return *this;
        }

    private:
        bool m_goodInit, m_useHierarchy, m_useHierarchyNext;
        unsigned int m_hierarchy;
        std::ofstream m_file;
};

extern Logger gLog;

#endif /* LOGGER_HPP */
