#pragma once
#include "Element.h"
#include "MotionBody.h"
#include "Point3D.h"

class Link :public Element
{
public:
    Link(const std::string& name,
         const std::string& type,
         const MotionBody& action,
         const MotionBody& base,
         const Point3D& actionConnection,
         const Point3D& baseConnection);

    MotionBody getAction()const;
    MotionBody getBase()const;
    Point3D getActionConnection() const;
    Point3D getBaseConnection() const;

protected:
    Point3D m_actionConnection;
    Point3D m_baseConnection;
    std::string type;
    MotionBody m_action;
    MotionBody m_base;
};