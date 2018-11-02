#pragma once
#include "Link.h"
#include "MotionBody.h"

class Joint :public Link
{
public:
    Joint(const std::string& name,const std::string& type,const MotionBody& action,const MotionBody& base);
    Joint();
};