#include "TopPerspective.h"
#include "Mechanism.h"

using namespace Perspective;

TopPerspective::TopPerspective()
{
}

QPointF TopPerspective::projectPoint(const DataModel::Point3D & point) const
{
    return QPointF(point.getX(),-point.getY());
}

QPointF TopPerspective::projectMotionBody(const DataModel::MotionBody & motionBody) const
{
    return projectPoint(motionBody.getOrigin());
}

QPointF TopPerspective::projectLinkAtachment(const DataModel::Link & link, DataModel::LinkType type) const
{
    switch (type) {
        case  DataModel::LinkType::Action:
            return projectPoint(link.getActionConnection());
            break;
        case  DataModel::LinkType::Base:
            return projectPoint(link.getBaseConnection());
            break;
        default:
            break;
    }
}
