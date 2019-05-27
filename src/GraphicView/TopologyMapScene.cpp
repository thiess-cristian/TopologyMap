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

#include <Panel\InfoPanel.h>

#include <qgraphicswidget.h>

using namespace GV;

TopologyMapScene::TopologyMapScene():QGraphicsScene()
{
    
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

void TopologyMapScene::addElements(std::shared_ptr<GM::Mechanism> mechanism)
{
    QGraphicsScene::clear();
    m_mechanism = mechanism;

    auto elements = mechanism->getElements();

    for (auto motionBody : elements[DataModel::ElementType::MotionBody]) {
        auto model = std::dynamic_pointer_cast<GM::MotionBody>(motionBody.second);        
        auto graphicMotionBody = new MotionBody(model);
        graphicMotionBody->setFlag(QGraphicsItem::ItemIsMovable);                
        m_elements.push_back(graphicMotionBody);        
        addItem(graphicMotionBody);

    }

    for (auto joint : elements[DataModel::ElementType::Joint]) {
        auto model = std::dynamic_pointer_cast<GM::Joint>(joint.second);
        auto graphicJoint = new Joint(std::dynamic_pointer_cast<GM::Joint>(joint.second));
        m_elements.push_back(graphicJoint);
        addItem(graphicJoint);
    }

    for (auto connector : elements[DataModel::ElementType::Connector]) {
        auto model = std::dynamic_pointer_cast<GM::Connector>(connector.second);        
        auto graphicConnector = new Connector(std::dynamic_pointer_cast<GM::Connector>(connector.second));
        m_elements.push_back(graphicConnector);
        addItem(graphicConnector);
    }

    Perspective::SidePerspective side;
    changeMotionBodiesPerspective(&side);
}

void TopologyMapScene::setInfoPanelRelations(std::shared_ptr<Panel::InfoPanel> infoPanel)
{
    for (auto& item : QGraphicsScene::items()) {
        auto topologyElement = dynamic_cast<GV::Element*>(item);

        if (topologyElement != nullptr) {
            QObject::connect(&topologyElement->getRightClickMenu(), &ElementRightClickMenu::sentData, infoPanel.get(), &Panel::InfoPanel::addInfoTab);
        }
    }
}

void TopologyMapScene::setViewableHeight(size_t height)
{
    m_viewableHeight = height;
}

void TopologyMapScene::setViewableWidth(size_t width)
{
    m_viewableWidth = width;
}

double TopologyMapScene::computeScaleFactor()
{
    double maxX = -DBL_MAX;
    double maxY = -DBL_MAX;

    auto elements = m_mechanism->getElements();

    for (const auto& motionBody : elements[DataModel::ElementType::MotionBody]) {
        maxX = std::max(maxX, motionBody.second->boundingRect().right());
        maxY = std::max(maxY, motionBody.second->boundingRect().bottom());
    }
    
    return std::min(m_viewableHeight / maxY,m_viewableWidth / maxX);
}

QPointF TopologyMapScene::computeTranslationPoint()
{
    double minX = 0;
    double minY = 0;

    auto elements = m_mechanism->getElements();

    for (const auto& motionBody : elements[DataModel::ElementType::MotionBody]) {
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
    auto containers = m_mechanism->getElements();
    auto motionBodies = containers[DataModel::ElementType::MotionBody];

    for (auto element : motionBodies) {
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
    auto elements = m_mechanism->getElements()[DataModel::ElementType::Joint];
    for (auto element : elements) {
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
    auto elements = m_mechanism->getElements()[DataModel::ElementType::Connector];
    for (auto element : elements) {
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
