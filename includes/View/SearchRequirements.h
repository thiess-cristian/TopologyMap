#pragma once

#include <string>

struct SearchRequirements
{
    std::string searchText="";
    bool motionBodyCheck = false;
    bool jointCheck = false;
    bool connectorCheck = false;
    bool matchCase = false;
    bool matchWhole = false;
    bool regEx = false;
};