#pragma once
#include "XMLTagNames.h"
#include <map>
#include <string>

template<typename T>
class IElementStringToEnum
{
public:

    virtual T getType(std::string type)
    {
        return m_names[type];
    }

protected:
    std::map<std::string, T> m_names;
};


