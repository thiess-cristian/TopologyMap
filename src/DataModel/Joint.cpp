#include "DataModel\Joint.h"
#include "DataModel\MotionBody.h"

using namespace DataModel;

Joint::Joint(const std::string & name, 
             const JointType & type, 
             std::shared_ptr<MotionBody> action,
             std::shared_ptr<MotionBody> base,
             const Point3D & actionConnection, 
             const Point3D & baseConnection):
    Link(name,"",action,base,actionConnection,baseConnection),
    m_type(type)
{}

Joint::Joint():Link("","",nullptr,nullptr,Point3D(),Point3D())
{}

JointType Joint::getType() const
{
    return m_type;
}

bool Joint::isEqual(const Element & other) const
{
    if (Joint const* p = dynamic_cast<Joint const*>(&other)) {
        return Link::isEqual(other) && m_type == p->m_type;
    } else {
        return false;
    }
}


