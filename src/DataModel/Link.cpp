#include "DataModel\Link.h"
#include "DataModel\MotionBody.h"

using namespace DataModel;

Link::Link(
    const std::string & name, 
    const std::string & type, 
    std::shared_ptr<MotionBody> action, 
    std::shared_ptr<MotionBody> base, 
    const Point3D & actionConnection, 
    const Point3D & baseConnection):
        Element(name),
        m_action(action),
        m_base(base),
        m_actionConnection(actionConnection),
        m_baseConnection(baseConnection)
{}

std::shared_ptr<MotionBody> Link::getAction() const
{
    return m_action;
}

std::shared_ptr<MotionBody> Link::getBase() const
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

bool Link::isEqual(const Element & other) const
{
    if (Link const* p = dynamic_cast<Link const*>(&other)) {
        return Element::isEqual(other) &&
            m_actionConnection == p->m_actionConnection &&
            m_baseConnection == p->m_baseConnection &&
            *m_base == *p->m_base &&
            *m_action == *p->m_action &&
            type == p->type;
    } else {
        return false;
    }
}


