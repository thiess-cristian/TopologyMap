#pragma once
#include "Element.h"
#include "MotionBody.h"

class Link :public Element
{
public:
    Link(const std::string& name,const std::string& type,const MotionBody& action,const MotionBody& base);

    MotionBody getAction()const;
    MotionBody getBase()const;

protected:
    std::string type;
    MotionBody m_action;
    MotionBody m_base;
};