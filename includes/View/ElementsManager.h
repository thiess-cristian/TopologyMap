#pragma once

#include "DocumentParser.h"
#include <vector>

class TopologyMapScene;
class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;

class ElementsManager
{
public:
    ElementsManager();
    
    void loadElements(QFile& file);
    void addElementsToScene(TopologyMapScene* scene);

private:

    std::vector<GraphicMotionBody*> m_motionBodies;
    std::vector<GraphicJoint*> m_joints;
    std::vector<GraphicConnector*> m_connectors;
};