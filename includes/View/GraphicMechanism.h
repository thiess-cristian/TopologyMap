#pragma once
#include "Mechanism.h"
#include <vector>

class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;

class GraphicMechanism
{
public:
    GraphicMechanism(const std::vector<GraphicMotionBody*>& graphicMotionBodies,
                     const std::vector<GraphicJoint*>& graphicJoints, 
                     const std::vector<GraphicConnector*>& graphicConnectors);
    GraphicMechanism();

    void setGraphicMotionBodies(const std::vector<GraphicMotionBody*>& graphicMotionBodies);
    void setGraphicJoints(const std::vector<GraphicJoint*>& graphicJoints);
    void setGraphicConnectors(const std::vector<GraphicConnector*>& graphicConnectors);

    const std::vector<GraphicMotionBody*>& getGraphicMotionBodies()const;
    const std::vector<GraphicJoint*>& getGraphicJoints()const;
    const std::vector<GraphicConnector*>& getGraphicConnectors()const;

    GraphicMotionBody* findMotionBody(const std::string& name) const;

private:
     std::vector<GraphicMotionBody*> m_graphicMotionBodies;
     std::vector<GraphicJoint*> m_graphicJoints;
     std::vector<GraphicConnector*> m_graphicConnector;
};