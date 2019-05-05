#pragma once
#include <string>

namespace DataModel
{
    class Element
    {
    public:
        Element(const std::string& name);        
        virtual ~Element() {};
        std::string getName()const;

        bool operator==(const Element& other);

    protected:
        std::string m_name;
    };
}