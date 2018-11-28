#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Enums.h"
#include "TopPerspectiveElementsCreator.h"
#include "SidePerspectiveElementsCreator.h"
#include "FrontPerspectiveElementsCreator.h"

#include <Normalization.h>

#include "qfile.h"
#include <memory>
#include <iostream>

ElementsManager::ElementsManager()
{

}

void ElementsManager::loadElements(QFile & file)
{
    DocumentParser parser;

    m_mechanism = parser.createMechanism(file);
    //scaleMechanism();
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

        std::cout << joint->x()<<" "<<joint->y();
    }

    for (const auto& connector : creator->createConnectors()) {
        scene->addItem(connector);
    }

    for (const auto& motionBody : creator->createMotionBodies()) {
        scene->addItem(motionBody);
    }
}

void ElementsManager::scaleMechanism()
{
    double maxX = -DBL_MAX;
    double maxY = -DBL_MAX;
    double maxZ = -DBL_MAX;

    for (const auto& body : m_mechanism->getMotionBodies()) {
        if (body.second.getX() > maxX) {
            maxX = body.second.getX();
        }

        if (body.second.getY() > maxY) {
            maxY = body.second.getY();
        }

        if (body.second.getZ() > maxZ) {
            maxZ = body.second.getZ();
        }

        for (const auto& connection : body.second.getConnectionPoints()) {
            if (connection.getX() > maxX) {
                maxX = connection.getX();
            }

            if (connection.getY() > maxY) {
                maxY = connection.getY();
            }

            if (connection.getZ() > maxZ) {
                maxZ = connection.getZ();
            }
        }
    }
    //set new values
    for (auto& body : m_mechanism->getMotionBodies()) {
        
        double newX=Utils::normalize(body.second.getX(), 0, maxX, 0, 500);
        double newY= Utils::normalize(body.second.getY(), 0, maxY, 0, 500);
        double newZ= Utils::normalize(body.second.getZ(), 0, maxZ, 0, 500);

        body.second.setX(newX);
        body.second.setY(newY);
        body.second.setZ(newZ);

        for (auto& connection : body.second.getConnectionPoints()) {
            double newX = Utils::normalize(connection.getX(), 0, maxX, 0, 500);
            double newY = Utils::normalize(connection.getY(), 0, maxY, 0, 500);
            double newZ = Utils::normalize(connection.getZ(), 0, maxZ, 0, 500);

            connection.setX(newX);
            connection.setY(newY);
            connection.setZ(newZ);

        }
    }
}

