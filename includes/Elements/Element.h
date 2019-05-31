#pragma once
#include <string>

class Element
{
public:
    Element(const std::string& name);
    virtual ~Element() = default;
    std::string getName()const;

    bool operator==(const Element& other);
    bool operator!=(const Element& other);

protected:
    std::string m_name;
};