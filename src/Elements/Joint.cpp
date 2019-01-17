#include "Joint.h"

Joint::Joint(const std::string & name, 
             const JointType & type, 
             const MotionBody & action, 
             const MotionBody & base, 
             const Point3D & actionConnection, 
             const Point3D & baseConnection):
    Link(name,"",action,base,actionConnection,baseConnection),
    m_type(type)
{}

Joint::Joint():Link("","",MotionBody(),MotionBody(),Point3D(),Point3D())
{}


