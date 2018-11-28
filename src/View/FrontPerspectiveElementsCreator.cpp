#include "FrontPerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

FrontPerspectiveElementsCreator::FrontPerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism)
{
    m_mechanism = mechanism;
}

QPoint FrontPerspectiveElementsCreator::projectPoint(const Point3D& point) const
{
    return QPoint(point.getZ(), point.getY());
}
