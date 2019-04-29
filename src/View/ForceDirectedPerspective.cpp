#include "ForceDirectedPerspective.h"
#include "Mechanism.h"
#include "Point3D.h"
#include <utility>

ForceDirectedPerspective::ForceDirectedPerspective(std::shared_ptr<Mechanism> mechanism):
    m_mechanism(mechanism)
{
    GraphType::GraphCoord<double> origin;

    for (const auto& motionBody : m_mechanism->getMotionBodies()) {
        auto node = std::make_shared<GraphType::GraphNode<MotionBody, double>>(motionBody.second, origin);
        graph.addNode(node);
    }

    for (const auto& joint : m_mechanism->getJoints()) {

        std::shared_ptr<GraphType::GraphNode<MotionBody, double>> baseNode;
        std::shared_ptr<GraphType::GraphNode<MotionBody, double>> actionNode;

        for (const auto& node : graph.nodes()) {
            if (node->getData() == joint.second.getAction()) {
                actionNode = node;
            }

            if (node->getData() == joint.second.getBase()) {
                baseNode = node;
            }
        }

        graph.addEdge(actionNode, baseNode);
    }

    for (const auto& connector : m_mechanism->getConnectors()) {

        std::shared_ptr<GraphType::GraphNode<MotionBody, double>> baseNode;
        std::shared_ptr<GraphType::GraphNode<MotionBody, double>> actionNode;

        for (const auto& node : graph.nodes()) {
            if (node->getData() == connector.second.getAction()) {
                actionNode = node;
            }

            if (node->getData() == connector.second.getBase()) {
                baseNode = node;
            }
        }

        graph.addEdge(actionNode, baseNode);
    }


    GraphType::ForceDirectedLayout<MotionBody, double> layout(graph);
    layout.runAlgorithm();
}

QPointF ForceDirectedPerspective::projectPoint(const Point3D & point) const
{
    return QPointF(point.getX(),point.getY());
}

QPointF ForceDirectedPerspective::projectMotionBody(const MotionBody & motionBody) const
{
    std::shared_ptr<GraphType::GraphNode<MotionBody, double>> node;

    for (const auto& n : graph.getNodes()) {
        if (n->getData() == motionBody) {
            node = n;
        }
    }

    double x = node->getPosition().getX();
    double y= node->getPosition().getY();
    
    return QPointF(x*500,y*500);
}

QPointF ForceDirectedPerspective::projectLinkAtachment(const Link & link, LinkType type) const
{
    auto motionbody = type == LinkType::Action ? link.getAction() : link.getBase();
    return projectMotionBody(motionbody);
}