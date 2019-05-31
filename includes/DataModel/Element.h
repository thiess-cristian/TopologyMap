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

        bool operator==(const Element& other) const;
        bool operator!=(const Element& other) const;

    protected:
        virtual bool isEqual(const Element& other) const;

        std::string m_name;
    };
}