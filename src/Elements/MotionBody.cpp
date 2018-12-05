#include "MotionBody.h"

MotionBody::MotionBody(const std::string& name,const Point3D& origin):
    Element(name),
    m_origin(origin)
{

}

std::string MotionBody::getName() const
{
    return m_name;
}

void MotionBody::addConnection(const Point3D& connection)
{
    m_connections.push_back(connection);
}

std::vector<Point3D> MotionBody::getConnectionPoints() const
{
    return m_connections;
}

Point3D MotionBody::getOrigin() const
{
    return m_origin;
}
