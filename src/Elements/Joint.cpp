#include "Joint.h"

Joint::Joint(const std::string& name,
             const std::string& type,
             MotionBody& action,
             MotionBody& base,
             const Point3D& actionConnection,
             const Point3D& baseConnection) :
    Link(name, type, action, base, actionConnection, baseConnection)
{

}

Joint::Joint():Link("","",MotionBody(),MotionBody(),Point3D(),Point3D())
{}


