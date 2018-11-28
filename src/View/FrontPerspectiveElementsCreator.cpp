#include "FrontPerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

FrontPerspectiveElementsCreator::FrontPerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism, double scaleFactor)
{
    m_mechanism = mechanism;
    m_scaleFactor = scaleFactor;
}

QPoint FrontPerspectiveElementsCreator::projectPoint(const Point3D& point) const
{
    return QPoint(point.getZ(), point.getY())*m_scaleFactor;
}
