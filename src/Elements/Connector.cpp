#include "Connector.h"

Connector::Connector(const std::string& kind, const std::string& name, const std::string& type, const MotionBody& action, const MotionBody& base):
    Link(name,type,action,base),
    m_kind(kind)
{

}

Connector::Connector(const std::string & kind, const std::string & name, const std::string & type, const Joint & joint):
    Link(name, type, joint.getAction(), joint.getBase()),
    m_kind(kind)
{

}

Connector::Connector():
    Link("","",MotionBody(),MotionBody()),
    m_kind("")
{

}
