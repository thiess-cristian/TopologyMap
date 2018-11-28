#include "TopPerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"


#include "Mechanism.h"

TopPerspectiveElementsCreator::TopPerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism, double scaleFactor)
{
    m_mechanism = mechanism;
    m_scaleFactor = scaleFactor;
}

QPoint TopPerspectiveElementsCreator::projectPoint(const Point3D & point) const
{
    return QPoint(point.getX(),point.getY())*m_scaleFactor;
}
