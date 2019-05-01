#pragma once
#include <string>

namespace DataModel
{
    class Element
    {
    public:
        Element(const std::string& name);        
        std::string getName()const;
        virtual ~Element() {};
    protected:
        std::string m_name;
    };
}