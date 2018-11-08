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
