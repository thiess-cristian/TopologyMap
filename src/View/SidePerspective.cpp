#include "SidePerspective.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

SidePerspective::SidePerspective()
{
}

QPointF SidePerspective::projectPoint(const Point3D & point) const
{
    return QPointF(point.getX(), -point.getZ());
}
