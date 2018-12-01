#include "GraphicMechanism.h"
#include "GraphicMotionBody.h"

GraphicMechanism::GraphicMechanism(
    const std::vector<GraphicMotionBody*>& graphicMotionBodies, 
    const std::vector<GraphicJoint*>& graphicJoints, 
    const std::vector<GraphicConnector*>& graphicConnectors):
    m_graphicMotionBodies(graphicMotionBodies),
    m_graphicJoints(graphicJoints),
    m_graphicConnector(graphicConnectors)
{

}

GraphicMechanism::GraphicMechanism()
{}

void GraphicMechanism::setGraphicMotionBodies(const std::vector<GraphicMotionBody*>& graphicMotionBodies)
{
    m_graphicMotionBodies = graphicMotionBodies;
}

void GraphicMechanism::setGraphicJoints(const std::vector<GraphicJoint*>& graphicJoints)
{
    m_graphicJoints = graphicJoints;
}

void GraphicMechanism::setGraphicConnectors(const std::vector<GraphicConnector*>& graphicConnectors)
{
    m_graphicConnector = graphicConnectors;
}

const std::vector<GraphicMotionBody*>& GraphicMechanism::getGraphicMotionBodies() const
{
    return m_graphicMotionBodies;
}

const std::vector<GraphicJoint*>& GraphicMechanism::getGraphicJoints() const
{
    return m_graphicJoints;
}

const std::vector<GraphicConnector*>& GraphicMechanism::getGraphicConnectors() const
{
    return m_graphicConnector;
}

GraphicMotionBody * GraphicMechanism::findMotionBody(const std::string & name) const
{
    for (const auto& motionBody : m_graphicMotionBodies) {
        if (motionBody->getModel().getName() == name) {
            return motionBody;
        }
    }
    return nullptr;
}
