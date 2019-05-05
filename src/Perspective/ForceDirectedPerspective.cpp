#include "ForceDirectedPerspective.h"
#include <DataModel\Mechanism.h>
#include <utility>

using namespace Perspective;

ForceDirectedPerspective::ForceDirectedPerspective(std::shared_ptr<DataModel::Mechanism> mechanism):
    m_mechanism(mechanism)
{    
    Graph::GraphCoord<double> origin;

    for (auto motionBody : m_mechanism->getContainer(DataModel::ElementType::MotionBody)) {
        auto casted = std::dynamic_pointer_cast<DataModel::MotionBody>(motionBody.second);
        auto node = std::make_shared<Graph::GraphNode<DataModel::MotionBody, double>>(*casted, origin);
        graph.addNode(node);
    }

    for (auto element : m_mechanism->getContainer(DataModel::ElementType::Joint)) {

        auto joint = std::dynamic_pointer_cast<DataModel::Link>(element.second);
        std::shared_ptr<Graph::GraphNode<DataModel::MotionBody, double>> baseNode;
        std::shared_ptr<Graph::GraphNode<DataModel::MotionBody, double>> actionNode;
               
        for (auto node : graph.nodes()) {
            if (node->getData() == *joint->getAction()) {
                actionNode = node;
            }

            if (node->getData() == *joint->getBase()) {
                baseNode = node;
            }
        }
        
        graph.addEdge(actionNode, baseNode);
    }

    for (auto element : m_mechanism->getContainer(DataModel::ElementType::Connector)) {

        auto connector= std::dynamic_pointer_cast<DataModel::Link>(element.second);

        std::shared_ptr<Graph::GraphNode<DataModel::MotionBody, double>> baseNode;
        std::shared_ptr<Graph::GraphNode<DataModel::MotionBody, double>> actionNode;
        
        for (auto node : graph.nodes()) {
            if (node->getData() == *connector->getAction()) {
                actionNode = node;
            }

            if (node->getData() == *connector->getBase()) {
                baseNode = node;
            }
        }
        
        graph.addEdge(actionNode, baseNode);
    }

    Graph::ForceDirectedLayout<DataModel::MotionBody, double> layout(graph);
    layout.runAlgorithm();
    
}

QPointF ForceDirectedPerspective::projectPoint(const DataModel::Point3D & point) const
{
    return QPointF(point.getX(),point.getY());
}

QPointF ForceDirectedPerspective::projectMotionBody(const DataModel::MotionBody & motionBody) const
{
    std::shared_ptr<Graph::GraphNode<DataModel::MotionBody, double>> node;

    for (const auto& n : graph.getNodes()) {
        if (n->getData() == motionBody) {
            node = n;
        }
    }

    double x = node->getPosition().getX();
    double y= node->getPosition().getY();
    
    return QPointF(x*500,y*500);
}

QPointF ForceDirectedPerspective::projectLinkAtachment(const DataModel::Link & link, DataModel::LinkType type) const
{
    auto motionbody = type == DataModel::LinkType::Action ? link.getAction() : link.getBase();
    return projectMotionBody(*motionbody);
}