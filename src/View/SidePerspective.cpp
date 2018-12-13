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

std::vector<QPointF> SidePerspective::projectMotionBody(const MotionBody & motionBody) const
{
    auto connections = motionBody.getConnectionPoints();
    connections.push_back(motionBody.getOrigin());

    std::vector<QPointF> projectedPoints;

    for (const auto& point : connections) {
        projectedPoints.push_back(projectPoint(point));
    }
    return projectedPoints;
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
