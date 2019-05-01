#pragma once
#include <string>
#include <map>

namespace DataHandler
{
    class Version
    {
    public:
        virtual const char* operator()(const char* text) const = 0;
        virtual const char* operator()(const std::string& text) const =0;
        

    protected:
        std::map<std::string,std::string> m_dictionary;

    };


}
