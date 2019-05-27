#include "GraphicModel\Mechanism.h"
#include "GraphicModel\MotionBody.h"
#include "GraphicModel\Connector.h"
#include "GraphicModel\Joint.h"
#include "DataModel\Mechanism.h"
#include "DataModel\MotionBody.h"
#include "DataModel\Connector.h"
#include "DataModel\Joint.h"

using namespace GM;

Mechanism::Mechanism(std::shared_ptr<DataModel::Mechanism> dataMechanism)
{
    auto motionBodies = dataMechanism->getContainer(DataModel::ElementType::MotionBody);

    for (auto motionBody : motionBodies) {
        auto graphicMotionBodyModel = std::make_shared<GM::MotionBody>(motionBody.second);
        m_elements[DataModel::ElementType::MotionBody][motionBody.first] = graphicMotionBodyModel;
    }

    /*
    auto linkAdd = [this,dataMechanism](auto key,auto dataType,auto graphicModelType) {
        auto linkContainer->dataMechanism->getContainer(key);

        for (const auto& link : linkContainer) {
            auto linkCast = std::dynamic_pointer_cast<decltype(dataType)>(link.second);
            auto action = m_elements[key][linkCast->getAction()->getName()];
            auto base = m_elements[key][linkCast->getBase()->getName()];
            auto graphicLinkModel = std::make_shared<decltype(graphicModelType)>(link.second, action, base);
        }
    };

    */
    auto joints = dataMechanism->getContainer(DataModel::ElementType::Joint);

    for (auto joint : joints) {
        auto jointCast = std::dynamic_pointer_cast<DataModel::Joint>(joint.second);
        auto action = m_elements[DataModel::ElementType::MotionBody][jointCast->getAction()->getName()];
        auto base = m_elements[DataModel::ElementType::MotionBody][jointCast->getBase()->getName()];
        auto graphicJointModel = std::make_shared<GM::Joint>(joint.second, action, base);
        m_elements[DataModel::ElementType::Joint][joint.first] = graphicJointModel;
    }

    auto connectors = dataMechanism->getContainer(DataModel::ElementType::Connector);

    for (const auto& connector : connectors) {
        auto connectorCast = std::dynamic_pointer_cast<DataModel::Connector>(connector.second);
        auto action = m_elements[DataModel::ElementType::MotionBody][connectorCast->getAction()->getName()];
        auto base = m_elements[DataModel::ElementType::MotionBody][connectorCast->getBase()->getName()];
        auto graphicConnectorModel = std::make_shared<GM::Connector>(connector.second, action, base);
        m_elements[DataModel::ElementType::Connector][connector.first] = graphicConnectorModel;
    }
}

std::map<DataModel::ElementType, std::map<std::string, std::shared_ptr<Element>>> Mechanism::getElements()const
{
    return m_elements;
}
