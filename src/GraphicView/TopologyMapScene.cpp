#include "GraphicView\TopologyMapScene.h"
#include "GraphicView\MotionBody.h"
#include "GraphicView\Joint.h"
#include "GraphicView\Connector.h"
#include <GraphicModel\Mechanism.h>
#include <GraphicModel\MotionBody.h>
#include <GraphicModel\Joint.h>
#include <GraphicModel\Connector.h>
#include <DataModel\Mechanism.h>

using namespace GV;

TopologyMapScene::TopologyMapScene(std::shared_ptr<GM::Mechanism> mechanism):QGraphicsScene()
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
