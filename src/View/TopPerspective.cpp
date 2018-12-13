#include "TopPerspective.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

#include "Mechanism.h"

TopPerspective::TopPerspective()
{
}

QPointF TopPerspective::projectPoint(const Point3D & point) const
{
    return QPointF(point.getX(),-point.getY());
}

QPointF TopPerspective::projectMotionBody(const MotionBody & motionBody) const
{
    return projectPoint(motionBody.getOrigin());
}

QPointF TopPerspective::projectLinkAtachment(const Link & link, LinkType type) const
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
