#include "FrontPerspective.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

FrontPerspective::FrontPerspective()
{
}

QPointF FrontPerspective::projectPoint(const Point3D& point) const
{
    return QPointF(point.getZ(), -point.getY());
}

QPointF FrontPerspective::projectMotionBody(const MotionBody & motionBody) const
{
    return projectPoint(motionBody.getOrigin());
}

QPointF FrontPerspective::projectLinkAtachment(const Link & link, LinkType type) const
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
