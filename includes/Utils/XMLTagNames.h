#pragma once
#include <string>
#include <map>

enum class ElementType
{
    MotionBody,
    Joint,
    Connector
};

enum class JointType
{
    Revolute,
    Slider,
    Cylindrical,
    Screw,
    Universal,
    Spherical,
    Planar,
    Fixed,
    ConstantVelocity,
    Atpoint,
    Inline,
    Inplane,
    Orientation,
    Parallel,
    Perpendicular
};

enum class ConnectorKind
{
    Spring,
    Damper,
    Bushing,
    BeamForce,
};
