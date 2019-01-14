#pragma once
#include <string>
#include <map>

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

enum class ConnectorName
{
    Spring,
    Damper,
};
