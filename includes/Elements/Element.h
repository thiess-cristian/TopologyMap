#pragma once
#include <string>

class Element
{
public:
    Element(const std::string& name);
protected:
    std::string m_name;
};