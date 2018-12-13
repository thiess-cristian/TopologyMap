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
QPointF SidePerspective::projectMotionBody(const MotionBody & motionBody) const
{
    return projectPoint(motionBody.getOrigin());
}

QPointF SidePerspective::projectLinkAtachment(const Link & link, LinkType type) const
{
    switch (type) {
        case  LinkType::Action:
            return projectPoint(link.getActionConnection());
            break;
        case  LinkType::Base:
            return projectPoint(link.getBaseConnection());
            break;
        default:
            break;
    }
}
