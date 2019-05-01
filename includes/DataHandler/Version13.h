#pragma once
#include "DataHandler\Version.h"

namespace DataHandler
{
    class Version13 :public Version
    {
    public:
        Version13();
        const char* operator()(const char* text) const override;
        const char* operator()(const std::string& text) const override;
    };


}