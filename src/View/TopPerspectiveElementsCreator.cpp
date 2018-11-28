#include "TopPerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"


#include "Mechanism.h"

TopPerspectiveElementsCreator::TopPerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism)
{
    m_mechanism = mechanism;
}

QPoint TopPerspectiveElementsCreator::projectPoint(const Point3D & point) const
{
    return QPoint(point.getX(),point.getY());
}
