#include "DocumentParser.h"
#include "LinkAtachment.h"
#include "qfile.h"
#include "Point3D.h"
#include <iostream>
#include <string>
#include <JointStringToEnum.h>
#include <ConnectorStringToEnum.h>


DocumentParser::DocumentParser():m_version(Version::V_13)
{
    m_motionBodyName[Version::V_13] = "MotionBody";
    m_motionBodiesName[Version::V_13] = "MotionBodies";
    m_selectedMotionBodyName[Version::V_13] = "SelectedMotionBody";

    m_motionBodyName[Version::V_12] = "Link";
    m_motionBodiesName[Version::V_12] = "Links";
    m_selectedMotionBodyName[Version::V_12] = "SelectedLink";
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

    readFileVersion();

    auto motionBodies=readMotionBodies();
    auto joints=readJoints(motionBodies);
    auto connectors=readConnectors(motionBodies, joints);

    return std::make_shared<Mechanism>(motionBodies, joints, connectors);
}

auto findPoint = [](QDomElement origin) {
    double x = origin.firstChildElement("X").attribute("Value").toDouble();
    double y = origin.firstChildElement("Y").attribute("Value").toDouble();
    double z = origin.firstChildElement("Z").attribute("Value").toDouble();

    return Point3D(x, y, z);
};

void DocumentParser::readFileVersion()
{
    auto version = m_root.attribute("Version").toDouble();

    if (version == 12) {
        m_version = Version::V_12;
    } else {
        m_version = Version::V_13;
    }
}

std::map<std::string, MotionBody> DocumentParser::readMotionBodies()
{
    QDomElement motionbodiesParent = m_root.firstChildElement(m_motionBodiesName[m_version]);

    QDomNodeList list = motionbodiesParent.elementsByTagName(m_motionBodyName[m_version]);

    std::map<std::string, MotionBody> motionBodies;

    for (int i = 0; i < list.size(); i++) {
        QDomElement item = list.at(i).toElement();

        std::string nameAttribute = item.attribute("Name").toStdString();

        QDomElement origin = item.firstChildElement("MassAndInertia").firstChildElement("TransformationMatrix").firstChildElement("Origin");

        Point3D originPoint = findPoint(origin);
        motionBodies[nameAttribute]= MotionBody(nameAttribute, originPoint);
    }

    //add ground motion body
    motionBodies["Ground"] = MotionBody("Ground");

    return motionBodies;
}

std::map<std::string, Joint> DocumentParser::readJoints(std::map<std::string, MotionBody>& motionBodies)
{
    QDomElement jointsParent = m_root.firstChildElement("Joints");

    QDomNodeList list = jointsParent.elementsByTagName("Joint");
    
    std::map<std::string, Joint> joints;

    JointStringToEnum converter;

    for (int i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string nameAttribute = element.attribute("Name").toStdString();
            std::string typeAttribute = element.attribute("Type").toStdString();

            auto type = converter.getType(typeAttribute);

            QDomElement action = element.firstChildElement("Action");
            QDomElement base = element.firstChildElement("Base");

            std::string actionAttribute=action.firstChildElement(m_selectedMotionBodyName[m_version]).attribute("Name").toStdString();
            std::string baseAttribute=base.firstChildElement(m_selectedMotionBodyName[m_version]).attribute("Name").toStdString();

            if (motionBodies.find(actionAttribute) != motionBodies.end() && motionBodies.find(baseAttribute) != motionBodies.end()) {
                MotionBody& actionBody = motionBodies.at(actionAttribute);
                //if the base is missing then its connected to the ground
                MotionBody& baseBody = baseAttribute != "" ? motionBodies.at(baseAttribute) : motionBodies.at("Ground");

                //the connection point for the action motionbody
                QDomElement actionOrigin = action.firstChildElement("TransformationMatrix").firstChildElement("Origin");
                Point3D actionConnection = findPoint(actionOrigin);

                //the connection point for the base motionbody
                QDomElement baseOrigin = base.firstChildElement("TransformationMatrix").firstChildElement("Origin");
                Point3D baseConnection = findPoint(baseOrigin);
                
                joints[nameAttribute] = Joint(nameAttribute, type, actionBody, baseBody, actionConnection, baseConnection);

                actionBody.addLinkAtachment(LinkAtachment(joints[nameAttribute], LinkType::Action));
                baseBody.addLinkAtachment(LinkAtachment(joints[nameAttribute], LinkType::Base));
            }
        }
    }
    return joints;
}

std::map<std::string, Connector> DocumentParser::readConnectors(std::map<std::string, MotionBody>& motionBodies,const std::map<std::string, Joint>& joints)
{
    QDomElement jointsParent = m_root.firstChildElement("Connectors");

    QDomNodeList list = jointsParent.childNodes();

    std::map<std::string, Connector> connectors;

    ConnectorStringToEnum converter;

    for (int i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string kindAttribute = element.nodeName().toStdString();
            auto kind = converter.getType(kindAttribute);

            std::string nameAttribute = element.attribute("Name").toStdString();
            std::string typeAttribute = element.attribute("Type").toStdString();

            QDomElement action = element.firstChildElement("Action");
            QDomElement base = element.firstChildElement("Base");

            std::string actionAttribute = action.firstChildElement(m_selectedMotionBodyName[m_version]).attribute("Name").toStdString();
            std::string baseAttribute = base.firstChildElement(m_selectedMotionBodyName[m_version]).attribute("Name").toStdString();

            if (actionAttribute == "" && baseAttribute == "") {
                QDomElement selectedJoint = element.firstChildElement("SelectedJoint");
                std::string jointName = selectedJoint.attribute("Name").toStdString();

                Joint joint = joints.at(jointName);
               
                connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, joint);

            } else {
                if (motionBodies.find(actionAttribute) != motionBodies.end() && motionBodies.find(baseAttribute) != motionBodies.end()) {
                    MotionBody& actionBody = motionBodies.at(actionAttribute);
                    MotionBody& baseBody = motionBodies.at(baseAttribute);

                    QDomElement actionOrigin = action.firstChildElement("TransformationMatrix").firstChildElement("Origin");
                    Point3D actionConnection = findPoint(actionOrigin);
                    //the connection point for the base motionbody

                    QDomElement baseOrigin = base.firstChildElement("TransformationMatrix").firstChildElement("Origin");
                    Point3D baseConnection = findPoint(baseOrigin);
                   
                    connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, actionBody, baseBody, actionConnection, baseConnection);
                }
            }
        }
    }
    return connectors;
}


