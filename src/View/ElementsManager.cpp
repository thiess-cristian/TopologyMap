#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "GraphicMechanism.h"
#include "Enums.h"
#include "SidePerspective.h"
#include "Bounder.h"

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
}

void ElementsManager::addElementsToScene(TopologyMapScene * scene)
{
    scene->clear();

    m_graphicsMechanism = std::make_shared<GraphicMechanism>(createMotionBodies(), createJoints(), createConnectors());

    for (const auto& joint : m_graphicsMechanism->getGraphicJoints()) {
        scene->addItem(joint);
    }

    for (const auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        scene->addItem(connector);
    }

    for (const auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        scene->addItem(motionBody);
    }

    SidePerspective side;
    changePerspective(&side);
}

void ElementsManager::scaleMechanism(size_t windowHeight, size_t windowWidth)
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
    double xFactor = std::min(windowHeight / maxX, windowWidth / maxX);
    double yFactor = std::min(windowHeight / maxY, windowWidth / maxY);
    double zFactor = std::min(windowHeight / maxZ, windowWidth / maxZ);

    m_scaleFactor = std::min(std::min(xFactor, yFactor), zFactor);
}



void ElementsManager::changePerspective(IPerspective* perspective)
{
    changeMotionBodiesPerspective(perspective);
    changeJointsPerspective(perspective);
    changeConnectorsPerspective(perspective);
}

std::vector<GraphicMotionBody*> ElementsManager::createMotionBodies() const
{
    std::vector<GraphicMotionBody*> motionBodies;
    for (const auto& item : m_mechanism->getMotionBodies()) {
        motionBodies.push_back(new GraphicMotionBody(item.second));
    }
    return motionBodies;
}

std::vector<GraphicJoint*> ElementsManager::createJoints() const
{
    std::vector<GraphicJoint*> graphicJoints;

    for (const auto& item : m_mechanism->getJoints()) {
        graphicJoints.push_back(new GraphicJoint(item.second,nullptr,nullptr));
    }
    return graphicJoints;;
}

std::vector<GraphicConnector*> ElementsManager::createConnectors() const
{
    std::vector<GraphicConnector*> graphicConnectors;

    for (const auto& item : m_mechanism->getConnectors()) {
        graphicConnectors.push_back(new GraphicConnector(item.second));
    }
    return graphicConnectors;
}

void ElementsManager::changeMotionBodiesPerspective(IPerspective * perspective)
{
    Bounder bounder;
    for (auto& motionbody : m_graphicsMechanism->getGraphicMotionBodies()) {
        auto origin = perspective->projectPoint(motionbody->getModel().getOrigin());

        auto connections = motionbody->getModel().getConnectionPoints();
        connections.push_back(motionbody->getModel().getOrigin());
      
        std::vector<QPointF> projectedPoints;

        for (const auto& point : connections) {
            projectedPoints.push_back(perspective->projectPoint(point));
        }

        QRectF box=bounder.createBoundingRect(projectedPoints);
        QRectF bounding = bounder.createBoundingRect({
            origin * 2 - box.bottomRight(),
            origin * 2 - box.bottomLeft(),
            origin * 2 - box.topLeft(),
            origin * 2 - box.topRight(),           
            box.bottomRight(),
            box.bottomLeft(),
            box.topLeft(),
            box.topRight()            
        });

        motionbody->setBoundingRect(bounding);
        motionbody->setOrigin(origin);
        motionbody->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void ElementsManager::changeJointsPerspective(IPerspective * perspective)
{
    for (auto& joint : m_graphicsMechanism->getGraphicJoints()) {
        QPointF actionConnection = perspective->projectPoint(joint->getModel().getActionConnection());
        joint->setActionConnection(actionConnection);
        QPointF baseConnection = perspective->projectPoint(joint->getModel().getBaseConnection());
        joint->setBaseConnection(baseConnection);
    }
}

void ElementsManager::changeConnectorsPerspective(IPerspective * perspective)
{
    for (auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        QPointF actionConnection = perspective->projectPoint(connector->getModel().getActionConnection());
        connector->setActionConnection(actionConnection);
        QPointF baseConnection = perspective->projectPoint(connector->getModel().getBaseConnection());
        connector->setBaseConnection(baseConnection);
    }
}

