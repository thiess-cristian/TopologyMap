#pragma once

#include "DocumentParser.h"
#include "Enums.h"
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
    void addElementsToScene(TopologyMapScene * scene, Perspective perspective);
    void scaleMechanism(size_t windowHeight,size_t windowWidth);

private:

    std::shared_ptr<Mechanism> m_mechanism = nullptr;
    double m_scaleFactor;

};