#include "MotionBody.h"

MotionBody::MotionBody(const std::string& name):Element(name)
{
    m_coord.setX(rand() % 200);
    m_coord.setY(rand() % 200);
}

MotionBody::MotionBody() : Element("")
{}

int MotionBody::getX()const
{
    return m_coord.x();
}

int MotionBody::getY()const
{
    return m_coord.y();
}
