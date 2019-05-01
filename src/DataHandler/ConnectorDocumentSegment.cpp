#include "DataHandler\ConnectorDocumentSegment.h"
#include "DataHandler\DocumentStrings.h"
#include <DataModel\Connector.h>
#include <DataModel\MotionBody.h>
#include <Utils\ConnectorStringToEnum.h>

using namespace DataHandler;

ConnectorDocumentSegment::ConnectorDocumentSegment(const QDomDocument & document):DocumentSegment(document)
{}

void ConnectorDocumentSegment::readSegment(std::shared_ptr<DataModel::Mechanism> mechanism)
{
    using namespace Doc;
    const auto& version = *m_version;
    auto root = m_document.firstChildElement();

    QDomElement jointsParent = root.firstChildElement(Connectors);

    QDomNodeList list = jointsParent.childNodes();

    std::map<std::string, std::shared_ptr<DataModel::Element>> connectors;    
    auto motionBodies = mechanism->getContainer(DataModel::ElementType::MotionBody);
    auto joints = mechanism->getContainer(DataModel::ElementType::Joint);
    ConnectorStringToEnum converter;

    for (int i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string kindAttribute = element.nodeName().toStdString();
            auto kind = converter.getType(kindAttribute);

            std::string nameAttribute = element.attribute(Name).toStdString();
            std::string typeAttribute = element.attribute(Type).toStdString();

            QDomElement action = element.firstChildElement(Action);
            QDomElement base = element.firstChildElement(Base);

            std::string actionAttribute = action.firstChildElement(version(SelectedMotionBody)).attribute(Name).toStdString();
            std::string baseAttribute = base.firstChildElement(version(SelectedMotionBody)).attribute(Name).toStdString();

            if (actionAttribute == "" && baseAttribute == "") {
                QDomElement selectedJoint = element.firstChildElement(SelectedJoint);
                std::string jointName = selectedJoint.attribute(Name).toStdString();

                auto joint = std::dynamic_pointer_cast<DataModel::Joint>(joints.at(jointName));
                auto connector = std::make_shared<DataModel::Connector>(kind, nameAttribute, typeAttribute, joint);
                connectors[nameAttribute] = connector;
                
                joint->getAction()->addLinkAtachment(DataModel::LinkAtachment(connector, DataModel::LinkType::Action));
                joint->getBase()->addLinkAtachment(DataModel::LinkAtachment(connector, DataModel::LinkType::Base));

            } else {
                if (motionBodies.find(actionAttribute) != motionBodies.end() && motionBodies.find(baseAttribute) != motionBodies.end()) {
                    auto actionBody = std::dynamic_pointer_cast<DataModel::MotionBody>(motionBodies.at(actionAttribute));
                    auto baseBody = std::dynamic_pointer_cast<DataModel::MotionBody>(motionBodies.at(baseAttribute));

                    QDomElement actionOrigin = action.firstChildElement(TransformationMatrix).firstChildElement(Origin);
                    auto actionConnection = readPoint(actionOrigin);
                    //the connection point for the base motionbody

                    QDomElement baseOrigin = base.firstChildElement(TransformationMatrix).firstChildElement(Origin);
                    auto baseConnection = readPoint(baseOrigin);
                    auto connector= std::make_shared<DataModel::Connector>(kind, nameAttribute, typeAttribute, actionBody, baseBody, actionConnection, baseConnection);
                    connectors[nameAttribute] = connector;

                    actionBody->addLinkAtachment(DataModel::LinkAtachment(connector, DataModel::LinkType::Action));
                    baseBody->addLinkAtachment(DataModel::LinkAtachment(connector, DataModel::LinkType::Base));
                }
            }
        }
    }
    mechanism->addDataContainer(connectors, DataModel::ElementType::Connector);
}
