#include "GraphicMechanism.h"
#include "GraphicMotionBody.h"

GraphicMechanism::GraphicMechanism(const std::map<std::string, GraphicMotionBody*>& graphicMotionBodies, 
                                   const std::map<std::string, GraphicJoint*>& graphicJoints, 
                                   const std::map<std::string, GraphicConnector*>& graphicConnectors): 
    m_graphicMotionBodies(graphicMotionBodies),
    m_graphicJoints(graphicJoints),
    m_graphicConnectors(graphicConnectors)
{}

GraphicMechanism::GraphicMechanism()
{}

void GraphicMechanism::setGraphicMotionBodies(const std::map<std::string, GraphicMotionBody*>& graphicMotionBodies)
{
    m_graphicMotionBodies = graphicMotionBodies;
}

void GraphicMechanism::setGraphicJoints(const std::map<std::string, GraphicJoint*>& graphicJoints)
{
    m_graphicJoints = graphicJoints;
}

void GraphicMechanism::setGraphicConnectors(const std::map<std::string, GraphicConnector*>& graphicConnectors)
{
    m_graphicConnectors = graphicConnectors;
}

std::map<std::string, GraphicMotionBody*> GraphicMechanism::getGraphicMotionBodies() const
{
    return m_graphicMotionBodies;
}

std::map<std::string, GraphicJoint*> GraphicMechanism::getGraphicJoints() const
{
    return m_graphicJoints;
}

std::map<std::string, GraphicConnector*> GraphicMechanism::getGraphicConnectors() const
{
    return m_graphicConnectors;
}

GraphicMotionBody * GraphicMechanism::findMotionBody(const std::string & name) const
{
    return m_graphicMotionBodies.at(name);
}
