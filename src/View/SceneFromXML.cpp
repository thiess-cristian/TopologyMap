#include "SceneFromXML.h"
#include "GraphicMechanism.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

SceneFromXML::SceneFromXML(std::string modelName):m_modelName(modelName)
{

}

void SceneFromXML::updateFromXML(std::shared_ptr<GraphicMechanism> mechanism, QFile & file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw "can't open";
    }

    if (!m_document.setContent(&file)) {
        throw "can't load file";
    }

    file.close();
    m_root = m_document.firstChildElement();

    if (m_modelName != m_root.attribute("model_name").toStdString()) {
        throw "wrong file";
    }

    updateMotionBodies(mechanism);
    updateJoints(mechanism->getGraphicJoints());
    updateConnectors(mechanism->getGraphicConnectors());
}

void SceneFromXML::updateMotionBodies(std::shared_ptr<GraphicMechanism> mechanism)
{
    QDomElement motionBodyParent = m_root.firstChildElement("MotionBodies");

    QDomNodeList motionBodiesList = motionBodyParent.elementsByTagName("MotionBody");

    for (int i = 0; i < motionBodiesList.size(); i++) {
        QDomNode item = motionBodiesList.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string name = element.attribute("name").toStdString();

            QDomElement origin = element.firstChildElement("Origin");

            double originX = origin.attribute("x").toDouble();
            double originY = origin.attribute("y").toDouble();

            auto motionBody = mechanism->findMotionBody(name);
            motionBody->setOrigin(QPointF(originX, originY));

            QDomElement boundingRect = element.firstChildElement("BoundingRect");

            double rectX = boundingRect.attribute("x").toDouble();
            double rectY = boundingRect.attribute("y").toDouble();
            double rectW = boundingRect.attribute("w").toDouble();
            double rectH = boundingRect.attribute("h").toDouble();

            motionBody->setBoundingRect(QRectF(rectX, rectY, rectW, rectH));
        }
    }
}

void SceneFromXML::updateJoints(std::map<std::string, GraphicJoint*> joints)
{
    QDomElement jointsParent = m_root.firstChildElement("Joints");

    QDomNodeList jointsList = jointsParent.elementsByTagName("Joint");

    for (int i = 0; i < jointsList.size(); i++) {
        QDomNode item = jointsList.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string name= element.attribute("name").toStdString();

            QDomElement action = element.firstChildElement("Action");

            double actionX = action.attribute("x").toDouble();
            double actionY = action.attribute("y").toDouble();

            QDomElement base = element.firstChildElement("Base");

            double baseX = base.attribute("x").toDouble();
            double baseY = base.attribute("y").toDouble();

            joints[name]->setBaseConnection(QPointF(baseX, baseY));
            joints[name]->setActionConnection(QPointF(actionX, actionY));
        }
    }
}

void SceneFromXML::updateConnectors(std::map<std::string, GraphicConnector*> connectors)
{
    QDomElement connectorsParent = m_root.firstChildElement("Connectors");

    QDomNodeList connectorsList = connectorsParent.elementsByTagName("Connector");

    for (int i = 0; i < connectorsList.size(); i++) {
        QDomNode item = connectorsList.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string name = element.attribute("name").toStdString();

            QDomElement action = element.firstChildElement("Action");

            double actionX = action.attribute("x").toDouble();
            double actionY = action.attribute("y").toDouble();

            QDomElement base = element.firstChildElement("Base");

            double baseX = base.attribute("x").toDouble();
            double baseY = base.attribute("y").toDouble();

            connectors[name]->setBaseConnection(QPointF(baseX, baseY));
            connectors[name]->setActionConnection(QPointF(actionX, actionY));
        }
    }
}
