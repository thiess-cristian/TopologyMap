#include "SidePerspective.h"

using namespace Perspective;

SidePerspective::SidePerspective()
{
}

QPointF SidePerspective::projectPoint(const DataModel::Point3D & point) const
{
    return QPointF(point.getX(), -point.getZ());
}
QPointF SidePerspective::projectMotionBody(const DataModel::MotionBody & motionBody) const
{
    return projectPoint(motionBody.getOrigin());
}

QPointF SidePerspective::projectLinkAtachment(const DataModel::Link & link, DataModel::LinkType type) const
{
    switch (type) {
        case DataModel::LinkType::Action:
            return projectPoint(link.getActionConnection());
            break;
        case DataModel::LinkType::Base:
            return projectPoint(link.getBaseConnection());
            break;
        default:
            break;
    }
}
