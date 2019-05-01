#include "DataHandler\Version12.h"
#include "DataHandler\DocumentStrings.h"

using namespace DataHandler;

Version12::Version12()
{
    m_dictionary[Doc::MotionBody] = "Link";
    m_dictionary[Doc::MotionBodies] = "Links";
    m_dictionary[Doc::SelectedMotionBody] = "SelectedLink";
}

const char* Version12::operator()(const char* text) const
{
    return m_dictionary.at(text).c_str();
}

const char * DataHandler::Version12::operator()(const std::string & text) const
{
    return m_dictionary.at(text).c_str();
}
