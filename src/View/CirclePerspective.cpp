#include "CirclePerspective.h"
#include "Mechanism.h"
#define _USE_MATH_DEFINES
#include <math.h>

CirclePerspective::CirclePerspective(std::shared_ptr<Mechanism> mechanism) :m_mechanism(mechanism)
{
   
}

QPointF CirclePerspective::projectPoint(const Point3D & point) const
{
    return QPointF();
}

QPointF CirclePerspective::projectMotionBody(const MotionBody & motionBody) const
{
    auto motionBodies = m_mechanism->getMotionBodies();
    double pos = std::distance(motionBodies.begin(), motionBodies.find(motionBody.getName()));

    double pi2 = 2.0*M_PI;

    double x = sin(pi2 / motionBodies.size() * pos);
    double y = cos(pi2 / motionBodies.size() * pos);
    return QPointF(x*100.0,y*100.0);
}

QPointF CirclePerspective::projectLinkAtachment(const Link & link, LinkType type) const
{
    auto motionbody= type == LinkType::Action ? link.getAction() : link.getBase();
    return projectMotionBody(motionbody);
}
