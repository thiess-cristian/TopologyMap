#include "DocumentParser.h"
#include "qfile.h"
#include <iostream>
#include <string>

DocumentParser::DocumentParser(QFile& file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw "can't open";
    }

    if (!m_document.setContent(&file)) {
        throw "can't load file";
    }

    file.close();
    m_root = m_document.firstChildElement();
}

DocumentParser::DocumentParser()
{

}

DocumentParser::~DocumentParser()
{

}

std::shared_ptr<Mechanism> DocumentParser::createMechanism(QFile& file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw "can't open";
    }

    if (!m_document.setContent(&file)) {
        throw "can't load file";
    }

    file.close();
    m_root = m_document.firstChildElement();

    auto motionBodies=readMotionBodies();
    auto joints=readJoints(motionBodies);
    auto connectors=readConnectors(motionBodies, joints);

    return std::make_shared<Mechanism>(motionBodies, joints, connectors);
}

std::map<std::string, MotionBody> DocumentParser::readMotionBodies()
{
    QDomElement motionbodiesParent = m_root.firstChildElement("MotionBodies");

    QDomNodeList list = motionbodiesParent.elementsByTagName("MotionBody");

    std::map<std::string, MotionBody> motionBodies;

    for (size_t i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        std::string nameAttribute = item.toElement().attribute("Name").toStdString();
        motionBodies[nameAttribute]= MotionBody(nameAttribute);     
    }

    //add ground motion body
    motionBodies["Ground"] = MotionBody("Ground");

    return motionBodies;
}

std::map<std::string, Joint> DocumentParser::readJoints(const std::map<std::string, MotionBody>& motionBodies)
{
    QDomElement jointsParent = m_root.firstChildElement("Joints");

    QDomNodeList list = jointsParent.elementsByTagName("Joint");
    
    std::map<std::string, Joint> joints;

    for (size_t i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string nameAttribute = element.attribute("Name").toStdString();
            std::string typeAttribute = element.attribute("Type").toStdString();

            QDomElement action = element.firstChildElement("Action");
            QDomElement base = element.firstChildElement("Base");

            std::string actionAttribute=action.firstChildElement("SelectedMotionBody").attribute("Name").toStdString();
            std::string baseAttribute=base.firstChildElement("SelectedMotionBody").attribute("Name").toStdString();

            MotionBody actionBody = motionBodies.at(actionAttribute);
            MotionBody baseBody;
            if (baseAttribute != "") {
                baseBody = motionBodies.at(baseAttribute);
            } else {
                baseBody = motionBodies.at("Ground");
            }

            joints[nameAttribute] = Joint(nameAttribute, typeAttribute, actionBody, baseBody);
        }
    }
    return joints;
}

std::map<std::string, Connector> DocumentParser::readConnectors(const std::map<std::string, MotionBody>& motionBodies,const std::map<std::string, Joint>& joints)
{
    QDomElement jointsParent = m_root.firstChildElement("Connectors");

    QDomNodeList list = jointsParent.childNodes();

    std::map<std::string, Connector> connectors;

    for (size_t i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string kind = element.nodeName().toStdString();

            std::string nameAttribute = element.attribute("Name").toStdString();
            std::string typeAttribute = element.attribute("Type").toStdString();

            QDomElement action = element.firstChildElement("Action");
            QDomElement base = element.firstChildElement("Base");

            //std::string actionAttribute = action.attribute("Name").toStdString();
            //std::string baseAttribute = base.attribute("Name").toStdString();

            std::string actionAttribute = action.firstChildElement("SelectedMotionBody").attribute("Name").toStdString();
            std::string baseAttribute = base.firstChildElement("SelectedMotionBody").attribute("Name").toStdString();


            if (actionAttribute == "" && baseAttribute == "") {
                QDomElement selectedJoint = element.firstChildElement("SelectedJoint");
                std::string jointName = selectedJoint.attribute("Name").toStdString();

                Joint joint = joints.at(jointName);

                connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, joint);

            } else {
                MotionBody actionBody = motionBodies.at(actionAttribute);
                MotionBody baseBody = motionBodies.at(baseAttribute);

                connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, actionBody, baseBody);

            }
        }
    }
    return connectors;
}


