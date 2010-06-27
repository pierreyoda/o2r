#include <sstream>
#include "Logger.hpp"

using namespace std;

Logger gLog;

Logger::Logger(const string &file) : m_goodInit(true), m_useHierarchy(false),
    m_useHierarchyNext(true), m_hierarchy(0), m_file(file.c_str())
{
    if (!m_file)
    {
        m_goodInit = false;
        throw "Log impossible : cannot open file " + file;
    }
}

Logger::~Logger()
{

}

void Logger::log(const string &toLog, const bool &useHierarchy)
{
    if (!m_file.is_open())
        return;
    if (useHierarchy || m_useHierarchy || m_useHierarchyNext)
    {
        m_useHierarchyNext = false;
        for (unsigned int i = 0; i < m_hierarchy; i++)
            m_file << "\t";
    }
    m_file << toLog;
}

