#include "FrontPerspective.h"
#include "Mechanism.h"

using namespace Perspective;

FrontPerspective::FrontPerspective()
{
}

QPointF FrontPerspective::projectPoint(const DataModel::Point3D& point) const
{
    return QPointF(point.getZ(), -point.getY());
}

QPointF FrontPerspective::projectMotionBody(const DataModel::MotionBody & motionBody) const
{
    return projectPoint(motionBody.getOrigin());
}

QPointF FrontPerspective::projectLinkAtachment(const DataModel::Link & link, DataModel::LinkType type) const
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
