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
