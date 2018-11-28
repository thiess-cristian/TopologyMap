#include "SidePerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

SidePerspectiveElementsCreator::SidePerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism)
{
    m_mechanism = mechanism;
}

QPoint SidePerspectiveElementsCreator::projectPoint(const Point3D & point) const
{
    return QPoint(point.getX(),point.getZ());
}
