#include "CirclePerspective.h"
#include "Mechanism.h"
#define _USE_MATH_DEFINES
#include <math.h>

CirclePerspective::CirclePerspective(std::shared_ptr<Mechanism> mechanism) :m_mechanism(mechanism)
{
    for (const auto& motionBody : m_mechanism->getMotionBodies()) {
        m_graph.addNode(motionBody.second);
    }

    for (const auto& joint : m_mechanism->getJoints()) {
        m_graph.addEdge(joint.second);
    }

    for (const auto& connector : m_mechanism->getConnectors()) {
        m_graph.addEdge(connector.second);
    }

    auto gr = m_graph.split();

    auto leaves = m_graph.popLeaves();
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
