#pragma once
#include "Element.h"
#include "MotionBody.h"

class Joint :public Element
{
public:
    Joint(const std::string& name,const std::string& type,const MotionBody& action,const MotionBody& base);
    Joint();

private:
    std::string m_type="";
    MotionBody m_action;
    MotionBody m_base;
};