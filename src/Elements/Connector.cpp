#include "Connector.h"

Connector::Connector(const std::string& kind,
                     const std::string& name,
                     const std::string& type,
                     MotionBody& action,
                     MotionBody& base,
                     const Point3D& actionConnection,
                     const Point3D& baseConnection):
    Link(name,type,action,base,actionConnection,baseConnection),
    m_kind(kind)
{

}

Connector::Connector(const std::string & kind, 
                     const std::string & name, 
                     const std::string & type, 
                     const Joint & joint):
    Link(name, 
         type, 
         joint.getAction(), 
         joint.getBase(),
         joint.getActionConnection(),
         joint.getBaseConnection()),
    m_kind(kind)
{

}

Connector::Connector():
    Link("","",MotionBody(),MotionBody(),Point3D(),Point3D()),
    m_kind("")
{

}
