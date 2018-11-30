#include "TopPerspective.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

#include "Mechanism.h"

TopPerspective::TopPerspective(double scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

QPointF TopPerspective::projectPoint(const Point3D & point) const
{
    return QPointF(point.getX(),point.getY())*m_scaleFactor;
}
