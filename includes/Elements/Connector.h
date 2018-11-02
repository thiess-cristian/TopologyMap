#pragma once
#include "Link.h"
#include "MotionBody.h"
#include "Joint.h"

class Connector:public Link
{
public:
    Connector(const std::string& kind,const std::string& name, const std::string& type, const MotionBody& action, const MotionBody& base);
    Connector(const std::string& kind, const std::string& name, const std::string& type, const Joint& joint);
    Connector();

private:
    std::string m_kind;
};