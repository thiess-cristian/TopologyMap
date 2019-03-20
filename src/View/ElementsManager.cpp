#include "ElementsManager.h"
#include "TopologyMapScene.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "GraphicMechanism.h"
#include "Enums.h"
#include "SidePerspective.h"
#include "Bounder.h"
#include "LinkAtachment.h"
#include "SceneToXML.h"
#include "SceneFromXML.h"
#include "OverlappingLinkFinder.h"

#include <qfile.h>
#include <qtransform.h>
#include <memory>
#include <iostream>
#include <map>
#include <set>

ElementsManager::ElementsManager()
{

}

void ElementsManager::openElements(QFile & file)
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
        scene->addItem(joint.second);
    }

    for (const auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        scene->addItem(connector.second);
    }

    for (const auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        scene->addItem(motionBody.second);
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

    OverlappingLinkFinder edgeFinder(m_graphicsMechanism);
    edgeFinder.computeOverlappingCount();    
}

double ElementsManager::computeScaleFactor()
{
    double maxX = -DBL_MAX;
    double maxY = -DBL_MAX;

    for (const auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        maxX = std::max(maxX, motionBody.second->boundingRect().right());
        maxY = std::max(maxY, motionBody.second->boundingRect().bottom());
    }

    return std::min((double)m_windowHeight / maxY, (double)m_windowWidth / maxX);
}

QPointF ElementsManager::computeTranslationPoint()
{
    double minX = 0;
    double minY = 0;

    for (const auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        minX = std::min(minX, motionBody.second->boundingRect().left());
        minY = std::min(minY, motionBody.second->boundingRect().top());
    }

    return QPointF(std::abs(minX),std::abs(minY));
}

void ElementsManager::applyScale(double scaleFactor)
{
    for (auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        motionBody.second->boundingRectScale(scaleFactor);    
    }

    for (auto & joint : m_graphicsMechanism->getGraphicJoints()) {
        joint.second->connectionScale(scaleFactor);
    }

    for (auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        connector.second->connectionScale(scaleFactor);
    }
}

void ElementsManager::applyTranslation(QPointF translatePoint)
{
    for (auto& motionBody : m_graphicsMechanism->getGraphicMotionBodies()) {
        motionBody.second->boundingRectTranslate(translatePoint);
    }

    for (auto & joint : m_graphicsMechanism->getGraphicJoints()) {
        joint.second->connectionTranslate(translatePoint);
    }

    for (auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        connector.second->connectionTranslate(translatePoint);
    }
}

std::shared_ptr<Mechanism> ElementsManager::getMechanism() const
{
    return m_mechanism;
}

std::shared_ptr<GraphicMechanism> ElementsManager::getGraphicMechanism() const
{
    return m_graphicsMechanism;
}

void ElementsManager::displayElementName(ElementType type, bool checked)
{
    auto displayName = [checked](auto elementContainer) {
        for (auto& element : elementContainer) {
            element.second->enableDisplayName(checked);
        }
    };


    switch (type) {
        case ElementType::MotionBody: {
            displayName(m_graphicsMechanism->getGraphicMotionBodies());
            break;
        }
        case ElementType::Joint: {
            displayName(m_graphicsMechanism->getGraphicJoints());
            break;
        }
        case ElementType::Connector: {
            displayName(m_graphicsMechanism->getGraphicConnectors());
            break;
        }
        default:
            break;
    }
}

void ElementsManager::saveElements(QFile & file, std::string modelName)
{
    SceneToXML sceneWriter(modelName);

    sceneWriter.writeToXml(m_graphicsMechanism, file);
}

void ElementsManager::loadElements(QFile & file, std::string modelName)
{
    SceneFromXML sceneReader(modelName);

    sceneReader.updateFromXML(m_graphicsMechanism, file);
}

std::map<std::string, GraphicMotionBody*> ElementsManager::createMotionBodies() const
{
    std::map<std::string, GraphicMotionBody*> motionBodies;
    for (const auto& item : m_mechanism->getMotionBodies()) {
        motionBodies.emplace(item.second.getName(),new GraphicMotionBody(item.second));
    }
    return motionBodies;
}

std::map<std::string, GraphicJoint*> ElementsManager::createJoints() const
{
    std::map<std::string, GraphicJoint*> graphicJoints;

    for (const auto& item : m_mechanism->getJoints()) {
        auto actionBody = m_graphicsMechanism->findMotionBody(item.second.getAction().getName());
        auto baseBody = m_graphicsMechanism->findMotionBody(item.second.getBase().getName());
        graphicJoints.emplace(item.second.getName(),new GraphicJoint(item.second, actionBody, baseBody));
    }
    return graphicJoints;
}

std::map<std::string, GraphicConnector*> ElementsManager::createConnectors() const
{
    std::map<std::string, GraphicConnector*> graphicConnectors;

    for (const auto& item : m_mechanism->getConnectors()) {
        auto actionBody = m_graphicsMechanism->findMotionBody(item.second.getAction().getName());
        auto baseBody = m_graphicsMechanism->findMotionBody(item.second.getBase().getName());
        graphicConnectors.emplace(item.second.getName(),new GraphicConnector(item.second, actionBody, baseBody));
    }
    return graphicConnectors;
}

void ElementsManager::changeMotionBodiesPerspective(IPerspective * perspective)
{
    Bounder bounder;
    for (auto& motionbody : m_graphicsMechanism->getGraphicMotionBodies()) {
        std::vector<QPointF> projectedPoints;

        for (const auto& link : motionbody.second->getModel().getLinkAtachments()) {
            projectedPoints.push_back(perspective->projectLinkAtachment(*link.get()));
        }

        auto origin = perspective->projectMotionBody(motionbody.second->getModel());
        projectedPoints.push_back(origin);
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

        motionbody.second->setBoundingRect(bounding);
        motionbody.second->setOrigin(origin);
        motionbody.second->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void ElementsManager::changeJointsPerspective(IPerspective * perspective)
{
    for (auto& joint : m_graphicsMechanism->getGraphicJoints()) {
        QPointF actionConnection = perspective->projectLinkAtachment(joint.second->getModel(), LinkType::Action);
        joint.second->setActionConnection(actionConnection);
        QPointF baseConnection = perspective->projectLinkAtachment(joint.second->getModel(), LinkType::Base);
        joint.second->setBaseConnection(baseConnection);
    }
}

void ElementsManager::changeConnectorsPerspective(IPerspective * perspective)
{
    for (auto& connector : m_graphicsMechanism->getGraphicConnectors()) {
        QPointF actionConnection = perspective->projectLinkAtachment(connector.second->getModel(), LinkType::Action);
        connector.second->setActionConnection(actionConnection);
        QPointF baseConnection = perspective->projectLinkAtachment(connector.second->getModel(), LinkType::Base);
        connector.second->setBaseConnection(baseConnection);
    }
}

void ElementsManager::setStackingOrder()
{
    for (auto& motionbody : m_graphicsMechanism->getGraphicMotionBodies()) {
        motionbody.second->setZValue(-1 * motionbody.second->boundingRect().height()*motionbody.second->boundingRect().width());
    }
}

