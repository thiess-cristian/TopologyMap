#include "DataHandler\JointDocumentSegment.h"
#include "DataHandler\DocumentStrings.h"
#include <DataModel\Joint.h>
#include <DataModel\MotionBody.h>
#include <Utils\JointStringToEnum.h>

using namespace DataHandler;

JointDocumentSegment::JointDocumentSegment(const QDomDocument & document):DocumentSegment(document)
{}

void JointDocumentSegment::readSegment(std::shared_ptr<DataModel::Mechanism> mechanism)
{
    using namespace Doc;
    const auto& version = *m_version;
    auto root = m_document.firstChildElement();
    QDomElement jointsParent = root.firstChildElement(Joints);
    QDomNodeList list = jointsParent.elementsByTagName(Joint);

    std::map<std::string, std::shared_ptr<DataModel::Element>> joints;
    auto motionBodies = mechanism->getContainer(DataModel::ElementType::MotionBody);    
    JointStringToEnum converter;

    for (int i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string nameAttribute = element.attribute(Name).toStdString();
            std::string typeAttribute = element.attribute(Type).toStdString();

            auto type = converter.getType(typeAttribute);

            QDomElement action = element.firstChildElement(Action);
            QDomElement base = element.firstChildElement(Base);

            std::string actionAttribute = action.firstChildElement(version(SelectedMotionBody)).attribute(Name).toStdString();
            std::string baseAttribute = base.firstChildElement(version(SelectedMotionBody)).attribute(Name).toStdString();

            if (motionBodies.find(actionAttribute) != motionBodies.end() && motionBodies.find(baseAttribute) != motionBodies.end()) {
                auto actionBody = std::dynamic_pointer_cast<DataModel::MotionBody>(motionBodies.at(actionAttribute));
                //if the base is missing then its connected to the ground
                auto baseBody = std::dynamic_pointer_cast<DataModel::MotionBody>(baseAttribute != "" ? motionBodies.at(baseAttribute) : motionBodies.at(Ground));

                //the connection point for the action motionbody
                QDomElement actionOrigin = action.firstChildElement(TransformationMatrix).firstChildElement(Origin);
                auto actionConnection = readPoint(actionOrigin);

                //the connection point for the base motionbody
                QDomElement baseOrigin = base.firstChildElement(TransformationMatrix).firstChildElement(Origin);
                auto baseConnection = readPoint(baseOrigin);
                
                auto joint= std::make_shared<DataModel::Joint>(nameAttribute, type, actionBody, baseBody, actionConnection, baseConnection);
                joints[nameAttribute] = joint;                               
                actionBody->addLinkAtachment(DataModel::LinkAtachment(joint, DataModel::LinkType::Action));
                baseBody->addLinkAtachment(DataModel::LinkAtachment(joint, DataModel::LinkType::Base));
            }
        }
    }
    mechanism->addDataContainer(joints, DataModel::ElementType::Joint);
}
