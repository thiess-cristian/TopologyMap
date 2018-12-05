#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "GraphicMechanism.h"
#include "Enums.h"
#include "SidePerspective.h"
#include "Bounder.h"

#include <qfile.h>
#include <qtransform.h>
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

    m_graphicsMechanism = std::make_shared<GraphicMechanism>();

    m_graphicsMechanism->setGraphicMotionBodies(createMotionBodies());
    m_graphicsMechanism->setGraphicJoints(createJoints());
    m_graphicsMechanism->setGraphicConnectors(createConnectors());


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

void ElementsManager::setWindowSize(size_t windowHeight, size_t windowWidth)
{
    m_windowHeight = windowHeight;
    m_windowWidth = windowWidth;
}


void ElementsManager::changePerspective(IPerspective* perspective)
{
    changeMotionBodiesPerspective(perspective);
    changeJointsPerspective(perspective);
    changeConnectorsPerspective(perspective);

    auto translationPoint = computeTranslationPoint();
    applyTranslation(translationPoint);

    double scaleFactor=computeScaleFactor();
    applyScale(scaleFactor);

    setStackingOrder();
}

double ElementsManager::computeScaleFactor()
{
    double maxX = -DBL_MAX;
    double maxY = -DBL_MAX;

    for (const auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        maxX = std::max(maxX, motionBody->boundingRect().right());
        maxY = std::max(maxY, motionBody->boundingRect().bottom());
    }

    return std::min((double)m_windowHeight / maxY, (double)m_windowWidth / maxX);
}

QPointF ElementsManager::computeTranslationPoint()
{
    double minX = 0;
    double minY = 0;

    for (const auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        minX = std::min(minX, motionBody->boundingRect().left());
        minY = std::min(minY, motionBody->boundingRect().top());
    }

    return QPointF(std::abs(minX),std::abs(minY));
}

void ElementsManager::applyScale(double scaleFactor)
{
    for (auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        motionBody->boundingRectScale(scaleFactor);    
    }

    for (auto & joint : m_graphicsMechanism->getGraphicJoints()) {
        joint->connectionScale(scaleFactor);
    }

    for (auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        connector->connectionScale(scaleFactor);
    }
}

void ElementsManager::applyTranslation(QPointF translatePoint)
{
    for (auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        motionBody->boundingRectTranslate(translatePoint);
    }

    for (auto & joint : m_graphicsMechanism->getGraphicJoints()) {
        joint->connectionTranslate(translatePoint);
    }

    for (auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        connector->connectionTranslate(translatePoint);
    }
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
        auto actionBody = m_graphicsMechanism->findMotionBody(item.second.getAction().getName());
        auto baseBody = m_graphicsMechanism->findMotionBody(item.second.getBase().getName());
        graphicJoints.push_back(new GraphicJoint(item.second, actionBody, baseBody));
    }
    return graphicJoints;;
}

std::vector<GraphicConnector*> ElementsManager::createConnectors() const
{
    std::vector<GraphicConnector*> graphicConnectors;

    for (const auto& item : m_mechanism->getConnectors()) {
        auto actionBody = m_graphicsMechanism->findMotionBody(item.second.getAction().getName());
        auto baseBody = m_graphicsMechanism->findMotionBody(item.second.getBase().getName());
        graphicConnectors.push_back(new GraphicConnector(item.second, actionBody, baseBody));
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

void ElementsManager::setStackingOrder()
{
    for (auto& motionbody : m_graphicsMechanism->getGraphicMotionBodies()) {
        motionbody->setZValue(-1*motionbody->boundingRect().height()*motionbody->boundingRect().width());
    }
}

