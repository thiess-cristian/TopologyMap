#include "ForceDirectedPerspective.h"
#include "Mechanism.h"
#include "Point3D.h"

ForceDirectedPerspective::ForceDirectedPerspective(std::shared_ptr<Mechanism> mechanism):
    m_mechanism(mechanism)
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
    m_graph.forceDirectedLayout();
}

QPointF ForceDirectedPerspective::projectPoint(const Point3D & point) const
{
    return QPointF(point.getX(),point.getY());
}

QPointF ForceDirectedPerspective::projectMotionBody(const MotionBody & motionBody) const
{
    auto node = m_graph.getNodeCoord(motionBody);
    return QPointF(node.x*500,node.y*500);
}

QPointF ForceDirectedPerspective::projectLinkAtachment(const Link & link, LinkType type) const
{
    auto motionbody = type == LinkType::Action ? link.getAction() : link.getBase();
    return projectMotionBody(motionbody);
}