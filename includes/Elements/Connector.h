#pragma once
#include "Link.h"
#include "Joint.h"

class Connector:public Link
{
public:
    Connector(const std::string& kind,
              const std::string& name, 
              const std::string& type, 
              const MotionBody& action, 
              const MotionBody& base, 
              const Point3D& actionConnection,
              const Point3D& baseConnection);
    Connector(const std::string& kind, const std::string& name, const std::string& type, const Joint& joint);
    Connector();

private:
    std::string m_kind;
};