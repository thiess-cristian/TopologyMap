#include "GraphicMechanism.h"

GraphicMechanism::GraphicMechanism(
    const std::vector<GraphicMotionBody*>& graphicMotionBodies, 
    const std::vector<GraphicJoint*>& graphicJoints, 
    const std::vector<GraphicConnector*>& graphicConnectors):
    m_graphicMotionBodies(graphicMotionBodies),
    m_graphicJoints(graphicJoints),
    m_graphicConnector(graphicConnectors)
{

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
