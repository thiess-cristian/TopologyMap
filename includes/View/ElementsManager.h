#pragma once

#include "DocumentParser.h"
#include "Enums.h"
#include <vector>

class TopologyMapScene;
class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;
class GraphicMechanism;
class IPerspective;

class ElementsManager
{
public:
    ElementsManager();
    
    void loadElements(QFile& file);
    void addElementsToScene(TopologyMapScene * scene);
    void scaleMechanism(size_t windowHeight,size_t windowWidth);
    void changePerspective(IPerspective* perspective);

private:
    std::vector<GraphicMotionBody*> createMotionBodies() const;
    std::vector<GraphicJoint*> createJoints() const;
    std::vector<GraphicConnector*> createConnectors() const;

    void changeMotionBodiesPerspective(IPerspective* perspective);
    void changeJointsPerspective(IPerspective* perspective);
    void changeConnectorsPerspective(IPerspective* perspective);

    std::shared_ptr<Mechanism> m_mechanism = nullptr;
    std::shared_ptr<GraphicMechanism> m_graphicsMechanism = nullptr;
    double m_scaleFactor;
};