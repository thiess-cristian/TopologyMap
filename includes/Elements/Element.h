#pragma once
#include <string>

class Element
{
public:
    Element(const std::string& name);
    std::string getName()const;
protected:
    std::string m_name;
};