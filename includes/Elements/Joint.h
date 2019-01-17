#pragma once
#include "Link.h"
#include "MotionBody.h"
#include "XMLTagNames.h"


class Joint :public Link
{
public:
    Joint(const std::string& name,
          const JointType& type,
          const MotionBody& action,
          const MotionBody& base,
          const Point3D& actionConnection,
          const Point3D& baseConnection);
    Joint();

private:
    JointType m_type;

};