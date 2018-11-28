#pragma once
#include "Link.h"
#include "MotionBody.h"

class Joint :public Link
{
public:
    Joint(const std::string& name,
          const std::string& type,
          MotionBody& action,
          MotionBody& base,
          const Point3D& actionConnection,
          const Point3D& baseConnection);
    Joint();
};