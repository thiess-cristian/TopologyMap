#include "DataHandler\Version13.h"
#include "DataHandler\DocumentStrings.h"

using namespace DataHandler;

Version13::Version13()
{
    m_dictionary[Doc::MotionBody] = "MotionBody";
    m_dictionary[Doc::MotionBodies] = "MotionBodies";
    m_dictionary[Doc::SelectedMotionBody] = "SelectedMotionBody";
}

const char* Version13::operator()(const char* text) const
{
    return m_dictionary.at(text).c_str();
}

const char * DataHandler::Version13::operator()(const std::string & text) const
{
    return m_dictionary.at(text).c_str();
}
