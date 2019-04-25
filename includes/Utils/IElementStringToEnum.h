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

    std::string getString(T enumName)
    {
        for (const auto& name : m_names) {
            if (name.second == enumName) {
                return name.first;
            }
        }
        return "";
    }
    
    std::map<std::string, T> getStrings() const
    {
        return m_names;
    }

protected:
    IElementStringToEnum()
    {
    }
    std::map<std::string, T> m_names;
};
