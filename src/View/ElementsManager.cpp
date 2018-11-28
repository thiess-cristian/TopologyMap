#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Enums.h"
#include "TopPerspectiveElementsCreator.h"
#include "SidePerspectiveElementsCreator.h"
#include "FrontPerspectiveElementsCreator.h"

#include "qfile.h"
#include <memory>

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

    std::unique_ptr<IPerspectiveElementsCreator> creator;

    switch (perspective) {
        case Perspective::TOP: {
            creator = std::make_unique<TopPerspectiveElementsCreator>(m_mechanism);
            break;
        }
        case Perspective::SIDE: {
            creator = std::make_unique<SidePerspectiveElementsCreator>(m_mechanism);
            break;
        }
        case Perspective::FRONT: {
            creator = std::make_unique<FrontPerspectiveElementsCreator>(m_mechanism);
            break;
        }
        default:
            break;
    }

    for (const auto& joint : creator->createJoints()) {
        scene->addItem(joint);
    }
    for (const auto& connector : creator->createConnectors()) {
        scene->addItem(connector);
    }
    for (const auto& motionBody : creator->createMotionBodies()) {
        scene->addItem(motionBody);
    }
}

void ElementsManager::scaleMechanism(size_t windowHeight, size_t windowWidth)
{


}

