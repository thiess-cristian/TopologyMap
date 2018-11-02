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

    initMotionBodies();
    initJoints();
    initConnectors();
}

DocumentParser::~DocumentParser()
{

}

std::map<std::string, MotionBody> DocumentParser::getMotionBodies() const
{
    return m_motionBodies;
}

std::map<std::string, Joint> DocumentParser::getJoints() const
{
    return m_joints;
}

std::map<std::string, Connector> DocumentParser::getConnectors() const
{
    return m_connectors;
}

void DocumentParser::initMotionBodies()
{
    QDomElement motionbodiesParent = m_root.firstChildElement("MotionBodies");

    QDomNodeList list = motionbodiesParent.elementsByTagName("MotionBody");

    for (size_t i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        std::string nameAttribute = item.toElement().attribute("Name").toStdString();
        m_motionBodies[nameAttribute]= MotionBody(nameAttribute);     
    }
}

void DocumentParser::initJoints()
{
    QDomElement jointsParent = m_root.firstChildElement("Joints");

    QDomNodeList list = jointsParent.elementsByTagName("Joint");
    

    for (size_t i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string nameAttribute = element.attribute("Name").toStdString();
            std::string typeAttribute = element.attribute("Type").toStdString();

            QDomElement action = element.firstChildElement("Action");
            QDomElement base = element.firstChildElement("Base");

            std::string actionAttribute=action.attribute("Name").toStdString();
            std::string baseAttribute=base.attribute("Name").toStdString();

            MotionBody actionBody = m_motionBodies[actionAttribute];
            MotionBody baseBody = m_motionBodies[baseAttribute];

            m_joints[nameAttribute] = Joint(nameAttribute, typeAttribute, actionBody, baseBody);
        }
    }
}

void DocumentParser::initConnectors()
{
    QDomElement jointsParent = m_root.firstChildElement("Connectors");

    QDomNodeList list = jointsParent.childNodes();

    for (size_t i = 0; i < list.size(); i++) {
        QDomNode item = list.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string kind = element.nodeName().toStdString();

            std::string nameAttribute = element.attribute("Name").toStdString();
            std::string typeAttribute = element.attribute("Type").toStdString();

            QDomElement action = element.firstChildElement("Action");
            QDomElement base = element.firstChildElement("Base");

            std::string actionAttribute = action.attribute("Name").toStdString();
            std::string baseAttribute = base.attribute("Name").toStdString();


            if (actionAttribute == "" && baseAttribute == "") {
                QDomElement selectedJoint = element.firstChildElement("SelectedJoint");
                std::string jointName = selectedJoint.attribute("Name").toStdString();

                Joint joint = m_joints[jointName];

                m_connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, joint);

            } else {
                MotionBody actionBody = m_motionBodies[actionAttribute];
                MotionBody baseBody = m_motionBodies[baseAttribute];

                m_connectors[nameAttribute] = Connector(kind, nameAttribute, typeAttribute, actionBody, baseBody);

            }
        }
    }

}


