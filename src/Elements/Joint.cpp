#include "Joint.h"

Joint::Joint(const std::string& name, const std::string& type, const MotionBody& action, const MotionBody& base):
    Link(name,type,action,base)
{

}

Joint::Joint():Link("","",MotionBody(),MotionBody())
{}


