#pragma once
#include "Element.h"
#include "Point3D.h"
#include <qpoint.h>

class MotionBody :public Element
{
public:
    MotionBody(const std::string& name="", const Point3D& origin=Point3D());

    int getX() const;
    int getY() const;
    int getZ() const;

private:
    //QPoint m_coord;

    Point3D m_origin;

};
