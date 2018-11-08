#include "MotionBody.h"

MotionBody::MotionBody(const std::string& name,const Point3D& origin):
    Element(name),
    m_origin(origin)
{
}

int MotionBody::getX() const
{
    return 0;
}

int MotionBody::getY() const
{
    return 0;//m_coord.y();
}

int MotionBody::getZ() const
{
    return 0;
}
