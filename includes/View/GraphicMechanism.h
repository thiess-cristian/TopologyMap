#pragma once
#include "Mechanism.h"
#include <vector>
#include <map>

class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;

class GraphicMechanism
{
public:
    GraphicMechanism(const std::map<std::string, GraphicMotionBody*>& graphicMotionBodies,
                     const std::map<std::string, GraphicJoint*>& graphicJoints,
                     const std::map<std::string, GraphicConnector*>& graphicConnectors);
    GraphicMechanism();

    void setGraphicMotionBodies(const std::map<std::string, GraphicMotionBody*>& graphicMotionBodies);
    void setGraphicJoints(const std::map<std::string, GraphicJoint*>& graphicJoints);
    void setGraphicConnectors(const std::map<std::string, GraphicConnector*>& graphicConnectors);

    std::map<std::string, GraphicMotionBody*> getGraphicMotionBodies()const;
    std::map<std::string, GraphicJoint*> getGraphicJoints()const;
    std::map<std::string, GraphicConnector*> getGraphicConnectors()const;

    GraphicMotionBody* findMotionBody(const std::string& name) const;

private:
     std::map<std::string, GraphicMotionBody*> m_graphicMotionBodies;
     std::map<std::string, GraphicJoint*> m_graphicJoints;
     std::map<std::string, GraphicConnector*> m_graphicConnectors;
};