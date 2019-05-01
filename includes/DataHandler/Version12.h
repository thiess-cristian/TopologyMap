#pragma once
#include "DataHandler\Version.h"

namespace DataHandler
{
    class Version12 :public Version
    {
    public:
        Version12();
        const char* operator()(const char* text) const override;
        const char* operator()(const std::string& text) const override;
    };


}