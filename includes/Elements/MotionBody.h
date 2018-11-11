#pragma once
#include "Element.h"
#include "Point3D.h"
#include <qpoint.h>
#include <vector>

class MotionBody :public Element
{
public:
    MotionBody(const std::string& name="", const Point3D& origin=Point3D());

    int getX() const;
    int getY() const;
    int getZ() const;

    void addConnection(const Point3D& connection);
    std::vector<Point3D> getConnectionPoints() const;
private:
    
    std::vector<Point3D> m_connections;
    Point3D m_origin;

};
