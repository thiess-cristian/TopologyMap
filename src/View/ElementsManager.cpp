#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Enums.h"

#include "qfile.h"

ElementsManager::ElementsManager()
{

}

void ElementsManager::loadElements(QFile & file)
{
    DocumentParser parser;

    m_mechanism = parser.createMechanism(file);
}

void ElementsManager::addElementsToScene(TopologyMapScene * scene,Perspective perspective)
{
    scene->clear();

    auto bodies = m_mechanism->getMotionBodies();
    auto joints = m_mechanism->getJoints();
    auto connectors = m_mechanism->getConnectors();

    for (const auto& joint : joints) {
        scene->addItem(new GraphicJoint(joint.second,perspective));
    }

    for (const auto& connector : connectors) {
        scene->addItem(new GraphicConnector(connector.second,perspective));
    }

    for (const auto& body : bodies) {
        scene->addItem(new GraphicMotionBody(body.second, perspective));
    }
}

