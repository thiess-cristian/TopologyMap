#include "DataModel\Connector.h"

using namespace DataModel;

Connector::Connector(const ConnectorKind & kind, 
                     const std::string & name, 
                     const std::string & type, 
                     std::shared_ptr<MotionBody> action,
                     std::shared_ptr<MotionBody> base,
                     const Point3D & actionConnection, 
                     const Point3D & baseConnection):
    Link(name, type, action, base, actionConnection, baseConnection),
    m_kind(kind)
{}

Connector::Connector(const ConnectorKind & kind, 
                     const std::string & name, 
                     const std::string & type, 
                     std::shared_ptr<Joint> joint):
    Link(name,
         type,
         joint->getAction(),
         joint->getBase(),
         joint->getActionConnection(),
         joint->getBaseConnection()),
    m_kind(kind)
{}

Connector::Connector():
    Link("","",nullptr, nullptr,Point3D(),Point3D())
{

}

ConnectorKind Connector::getKind() const
{
    return m_kind;
}

bool Connector::isEqual(const Element & other) const
{
    if (Connector const* p = dynamic_cast<Connector const*>(&other)) {
        return Link::isEqual(other) && m_kind == p->m_kind;
    } else {
        return false;
    }
}
