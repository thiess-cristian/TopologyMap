#include "JointStringToEnum.h"

JointStringToEnum::JointStringToEnum()
{
    m_names["Revolute"] =         JointName::Revolute;
    m_names["Slider"] =           JointName::Slider;
    m_names["Cylindrical"] =      JointName::Cylindrical;
    m_names["Screw"] =            JointName::Screw;
    m_names["Universal"] =        JointName::Universal;
    m_names["Spherical"] =        JointName::Spherical;
    m_names["Planar"] =           JointName::Planar;
    m_names["Fixed"] =            JointName::Fixed;
    m_names["ConstantVelocity"] = JointName::ConstantVelocity;
    m_names["Atpoint"] =          JointName::Atpoint;
    m_names["Inline"] =           JointName::Inline;
    m_names["Inplane"] =          JointName::Inplane;
    m_names["Orientation"] =      JointName::Orientation;
    m_names["Parallel"] =         JointName::Parallel;
    m_names["Perpendicular"] =    JointName::Perpendicular;
}

