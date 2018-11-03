#include "Link.h"

Link::Link(const std::string& name, const std::string& type, const MotionBody& action, const MotionBody& base):
    Element(name),
    m_action(action),
    m_base(base)
{}


MotionBody Link::getAction() const
{
    return m_action;
}

MotionBody Link::getBase() const
{
    return m_base;
}

