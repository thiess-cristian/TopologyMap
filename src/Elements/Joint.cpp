#include "Joint.h"

Joint::Joint(const std::string& name, const std::string& type, const MotionBody& action, const MotionBody& base):
    Element(name),
    m_type(type),
    m_action(action),
    m_base(base)
{

}

Joint::Joint():Element("")
{}
