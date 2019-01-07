#include "Point3D.h"

Point3D::Point3D(double x, double y, double z):m_x(x),m_y(y),m_z(z)
{

}

double Point3D::getX() const
{
    return m_x;
}

double Point3D::getY() const
{
    return m_y;
}

double Point3D::getZ() const
{
    return m_z;
}

void Point3D::setX(double value)
{
    m_x = value;
}

void Point3D::setY(double value)
{
    m_y = value;
}

void Point3D::setZ(double value)
{
    m_z = value;
}

bool Point3D::operator==(const Point3D & point) const
{
    return m_x == point.m_x && m_y == point.m_y && m_z == point.m_z;
}
