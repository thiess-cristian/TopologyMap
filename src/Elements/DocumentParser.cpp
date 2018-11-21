#include "DocumentParser.h"
#include "qfile.h"
#include "Point3D.h"
#include <iostream>
#include <string>

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
        QDomElement item = list.at(i).toElement();

        std::string nameAttribute = item.attribute("Name").toStdString();

        QDomElement origin = item.firstChildElement("MassAndInertia").firstChildElement("TransformationMatrix").firstChildElement("Origin");

        double originX = origin.firstChildElement("X").attribute("Value").toDouble();
        double originY = origin.firstChildElement("Y").attribute("Value").toDouble();
        double originZ = origin.firstChildElement("Z").attribute("Value").toDouble();

        motionBodies[nameAttribute]= MotionBody(nameAttribute,Point3D(originX,originY,originZ));     
    }

    //add ground motion body
    motionBodies["Ground"] = MotionBody("Ground");

    return motionBodies;
}

auto findPoint = [](QDomElement origin) {
    double x = origin.firstChildElement("X").attribute("Value").toDouble();
    double y = origin.firstChildElement("Y").attribute("Value").toDouble();
    double z = origin.firstChildElement("Z").attribute("Value").toDouble();

    return Point3D(x, y, z);
};

std::map<std::string, Joint> DocumentParser::readJoints(std::map<std::string, MotionBody>& motionBodies)
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

            MotionBody& actionBody = motionBodies.at(actionAttribute);
            //if the base is missing then its connected to the ground
            MotionBody& baseBody = baseAttribute != "" ? motionBodies.at(baseAttribute) : motionBodies.at("Ground");
            
            //the connection point for the action motionbody
            QDomElement actionOrigin = action.firstChildElement("Point").firstChildElement("Origin");
            Point3D actionConnection = findPoint(actionOrigin);
            actionBody.addConnection(actionConnection);

            //the connection point for the base motionbody
            QDomElement baseOrigin = base.firstChildElement("Point").firstChildElement("Origin");
            Point3D baseConnection = findPoint(baseOrigin);
            baseBody.addConnection(baseConnection);
           
            joints[nameAttribute] = Joint(nameAttribute, typeAttribute, actionBody, baseBody,Point3D(), Point3D());

            
        }
    }
    return joints;
}

std::map<std::string, Connector> DocumentParser::readConnectors(std::map<std::string, MotionBody>& motionBodies,const std::map<std::string, Joint>& joints)
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
                MotionBody& actionBody = motionBodies.at(actionAttribute);
                MotionBody& baseBody = motionBodies.at(baseAttribute);

                QDomElement actionOrigin = action.firstChildElement("Point").firstChildElement("Origin");
                Point3D actionConnection = findPoint(actionOrigin);
                actionBody.addConnection(actionConnection);
                //the connection point for the base motionbody

                QDomElement baseOrigin = base.firstChildElement("Point").firstChildElement("Origin");
                Point3D baseConnection = findPoint(baseOrigin);
                baseBody.addConnection(baseConnection);


                connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, actionBody, baseBody, actionConnection, baseConnection);

            }
        }
    }
    return connectors;
}


