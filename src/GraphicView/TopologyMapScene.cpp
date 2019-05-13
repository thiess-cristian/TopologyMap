#include "GraphicView\TopologyMapScene.h"
#include "GraphicView\MotionBody.h"
#include "GraphicView\Joint.h"
#include "GraphicView\Connector.h"
#include <GraphicModel\Mechanism.h>
#include <GraphicModel\MotionBody.h>
#include <GraphicModel\Joint.h>
#include <GraphicModel\Connector.h>
#include <GraphicModel\Element.h>
#include <GraphicModel\Bounder.h>
#include <GraphicModel\OverlappingLinkFinder.h>
#include <DataModel\Mechanism.h>

#include <Perspective\TopPerspective.h>
#include <Perspective\SidePerspective.h>
#include <Perspective\FrontPerspective.h>
#include <Perspective\CirclePerspective.h>
#include <Perspective\ForceDirectedPerspective.h>

using namespace GV;

TopologyMapScene::TopologyMapScene(std::shared_ptr<GM::Mechanism> mechanism):QGraphicsScene(),m_mechanism(mechanism)
{
    auto elements = mechanism->getElements();
    
    for (const auto& motionBody : elements[DataModel::ElementType::MotionBody]) {
        auto graphicMotionBody = new MotionBody(std::dynamic_pointer_cast<GM::MotionBody>(motionBody.second));
        addItem(graphicMotionBody);
    }
    
    for (const auto& joint : elements[DataModel::ElementType::Joint]) {
        auto graphicJoint = new Joint(std::dynamic_pointer_cast<GM::Joint>(joint.second));
        addItem(graphicJoint);
    }

    for (const auto& connector : elements[DataModel::ElementType::Connector]) {
        auto graphicConnector = new Connector(std::dynamic_pointer_cast<GM::Connector>(connector.second));
        addItem(graphicConnector);
    }
}

void TopologyMapScene::changePerspective(Perspective::IPerspective* perspective)
{
    changeMotionBodiesPerspective(perspective);
    changeJointsPerspective(perspective);
    changeConnectorsPerspective(perspective);

    auto translationPoint = computeTranslationPoint();
    applyTranslation(translationPoint);

    double scaleFactor = computeScaleFactor();
    applyScale(scaleFactor);

    setStackingOrder();

    GM::OverlappingLinkFinder edgeFinder(m_mechanism);
    edgeFinder.computeOverlappingCount();
}

double TopologyMapScene::computeScaleFactor()
{
    double maxX = -DBL_MAX;
    double maxY = -DBL_MAX;

    for (const auto& motionBody : m_mechanism->getElements()[DataModel::ElementType::MotionBody]) {
        maxX = std::max(maxX, motionBody.second->boundingRect().right());
        maxY = std::max(maxY, motionBody.second->boundingRect().bottom());
    }
    
    return std::min(height() / maxY,width() / maxX);
}

QPointF TopologyMapScene::computeTranslationPoint()
{
    double minX = 0;
    double minY = 0;

    for (const auto& motionBody : m_mechanism->getElements()[DataModel::ElementType::MotionBody]) {
        minX = std::min(minX, motionBody.second->boundingRect().left());
        minY = std::min(minY, motionBody.second->boundingRect().top());
    }

    return QPointF(std::abs(minX), std::abs(minY));
}


void TopologyMapScene::applyScale(double scaleFactor)
{    
    for (auto& elementContainer : m_mechanism->getElements()) {
        for (auto& element : elementContainer.second) {
            element.second->scale(scaleFactor);
        }
    }
}


void TopologyMapScene::applyTranslation(QPointF translatePoint)
{    
    for (auto& elementContainer : m_mechanism->getElements()) {
        for (auto& element : elementContainer.second) {
            element.second->translate(translatePoint);
        }
    }
}


void TopologyMapScene::changeMotionBodiesPerspective(Perspective::IPerspective * perspective)
{
    GM::Bounder bounder;
    for (auto element : m_mechanism->getElements()[DataModel::ElementType::MotionBody]) {
        auto motionBody = std::dynamic_pointer_cast<GM::MotionBody>(element.second);
        std::vector<QPointF> projectedPoints;

        auto dataModel = std::dynamic_pointer_cast<DataModel::MotionBody>(motionBody->getDataModel());
        auto linkAtachments = dataModel->getLinkAtachments();

        for (const auto& link : linkAtachments) {
            projectedPoints.push_back(perspective->projectLinkAtachment(link));
        }

        auto origin = perspective->projectMotionBody(*dataModel);
        projectedPoints.push_back(origin);
        QRectF box = bounder.createBoundingRect(projectedPoints);
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

        motionBody->setBody(bounding);  

        //TODO: move this
        //motionbody.second->setFlag(QGraphicsItem::ItemIsMovable);
    }
}

void TopologyMapScene::changeJointsPerspective(Perspective::IPerspective * perspective)
{
    for (auto element : m_mechanism->getElements()[DataModel::ElementType::Joint]) {
        auto joint = std::dynamic_pointer_cast<GM::Joint>(element.second);
        auto dataModel = std::dynamic_pointer_cast<DataModel::Link>(joint->getDataModel());
        QPointF actionConnection = perspective->projectLinkAtachment(*dataModel, DataModel::LinkType::Action);
        joint->setActionConnection(actionConnection);
        QPointF baseConnection = perspective->projectLinkAtachment(*dataModel, DataModel::LinkType::Base);
        joint->setBaseConnection(baseConnection);
    }
}

void TopologyMapScene::changeConnectorsPerspective(Perspective::IPerspective * perspective)
{
    for (auto element : m_mechanism->getElements()[DataModel::ElementType::Connector]) {
        auto connector = std::dynamic_pointer_cast<GM::Connector>(element.second);
        auto dataModel = std::dynamic_pointer_cast<DataModel::Link>(connector->getDataModel());
        QPointF actionConnection = perspective->projectLinkAtachment(*dataModel, DataModel::LinkType::Action);
        connector->setActionConnection(actionConnection);
        QPointF baseConnection = perspective->projectLinkAtachment(*dataModel, DataModel::LinkType::Base);
        connector->setBaseConnection(baseConnection);
    }
}

void TopologyMapScene::setStackingOrder()
{
    //TODO: move this
    /*
    for (auto motionbody : m_mechanism->getElements()[DataModel::ElementType::MotionBody]) {
        motionbody.second->setZValue(-1 * motionbody.second->boundingRect().height()*motionbody.second->boundingRect().width());
    }
    */
    
}
