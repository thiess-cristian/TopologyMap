#include "Perspective\CirclePerspective.h"
#include <DataModel\Mechanism.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Perspective;

CirclePerspective::CirclePerspective(std::shared_ptr<DataModel::Mechanism> mechanism) :m_mechanism(mechanism)
{
   
}

QPointF CirclePerspective::projectPoint(const DataModel::Point3D & point) const
{
    return QPointF();
}

QPointF CirclePerspective::projectMotionBody(const DataModel::MotionBody & motionBody) const
{
    auto motionBodies = m_mechanism->getContainer(DataModel::ElementType::MotionBody);
    double pos = std::distance(motionBodies.begin(), motionBodies.find(motionBody.getName()));

    double pi2 = 2.0*M_PI;

    double x = sin(pi2 / motionBodies.size() * pos);
    double y = cos(pi2 / motionBodies.size() * pos);
    return QPointF(x*100.0,y*100.0);
}

QPointF CirclePerspective::projectLinkAtachment(const DataModel::Link & link, DataModel::LinkType type) const
{
    auto motionbody= type == DataModel::LinkType::Action ? link.getAction() : link.getBase();
    return projectMotionBody(*motionbody);
}
