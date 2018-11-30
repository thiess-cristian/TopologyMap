#include "FrontPerspective.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

FrontPerspective::FrontPerspective(double scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

QPointF FrontPerspective::projectPoint(const Point3D& point) const
{
    return QPointF(point.getZ(), point.getY())*m_scaleFactor;
}
