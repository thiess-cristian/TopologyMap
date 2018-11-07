#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

#include "qfile.h"

ElementsManager::ElementsManager()
{

}

void ElementsManager::loadElements(QFile & file)
{
    DocumentParser parser;

    std::shared_ptr<Mechanism> mechanism=parser.createMechanism(file);

    auto bodies= mechanism->getMotionBodies();
    auto joints= mechanism->getJoints();
    auto connectors= mechanism->getConnectors();

    for (const auto& body : bodies) {
        m_motionBodies.push_back(new GraphicMotionBody(body.second));
    }

    for (const auto& joint : joints) {
        m_joints.push_back(new GraphicJoint(joint.second));
    }

    for (const auto& connector : connectors) {
        m_connectors.push_back(new GraphicConnector(connector.second));
    }
}

void ElementsManager::addElementsToScene(TopologyMapScene * scene)
{
    for (const auto& joint : m_joints) {
        scene->addItem(joint);
    }

    for (const auto& connector : m_connectors) {
        scene->addItem(connector);
    }

    for (const auto& body : m_motionBodies) {
        scene->addItem(body);
    }
}

