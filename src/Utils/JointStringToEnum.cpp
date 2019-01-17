#include "JointStringToEnum.h"

JointStringToEnum::JointStringToEnum()
{
    m_names["Revolute"] =         JointType::Revolute;
    m_names["Slider"] =           JointType::Slider;
    m_names["Cylindrical"] =      JointType::Cylindrical;
    m_names["Screw"] =            JointType::Screw;
    m_names["Universal"] =        JointType::Universal;
    m_names["Spherical"] =        JointType::Spherical;
    m_names["Planar"] =           JointType::Planar;
    m_names["Fixed"] =            JointType::Fixed;
    m_names["ConstantVelocity"] = JointType::ConstantVelocity;
    m_names["Atpoint"] =          JointType::Atpoint;
    m_names["Inline"] =           JointType::Inline;
    m_names["Inplane"] =          JointType::Inplane;
    m_names["Orientation"] =      JointType::Orientation;
    m_names["Parallel"] =         JointType::Parallel;
    m_names["Perpendicular"] =    JointType::Perpendicular;
}

