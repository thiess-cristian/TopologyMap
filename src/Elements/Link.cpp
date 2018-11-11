#include "Link.h"

Link::Link(const std::string& name,
           const std::string& type,
           const MotionBody& action,
           const MotionBody& base,
           const Point3D& actionConnection,
           const Point3D& baseConnection):
    Element(name),
    m_action(action),
    m_base(base),
    m_actionConnection(actionConnection),
    m_baseConnection(baseConnection)
{}


MotionBody Link::getAction() const
{
    return m_action;
}

MotionBody Link::getBase() const
{
    return m_base;
}

Point3D Link::getActionConnection() const
{
    return m_actionConnection;
}

Point3D Link::getBaseConnection() const
{
    return m_baseConnection;
}

