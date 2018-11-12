#include "MotionBody.h"

MotionBody::MotionBody(const std::string& name,const Point3D& origin):
    Element(name),
    m_origin(origin)
{
}

int MotionBody::getX() const
{
    return m_origin.getX();
}

int MotionBody::getY() const
{
    return m_origin.getY();
}

int MotionBody::getZ() const
{
    return m_origin.getZ();
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
