#include "SceneFromXML.h"
#include "DocumentStrings.h"
#include <GraphicModel\Element.h>
#include <GraphicModel\Mechanism.h>
#include <GraphicModel\Joint.h>
#include <GraphicModel\Connector.h>
#include <GraphicModel\MotionBody.h>

using namespace DataHandler;

SceneFromXML::SceneFromXML(std::string modelName):m_modelName(modelName)
{

}

void SceneFromXML::updateFromXML(std::shared_ptr<GM::Mechanism> mechanism, QFile & file)
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

    updateMotionBodies(mechanism->getElements()[DataModel::ElementType::MotionBody]);
    updateJoints(mechanism->getElements()[DataModel::ElementType::Joint]);
    updateConnectors(mechanism->getElements()[DataModel::ElementType::Connector]);
}

void SceneFromXML::updateMotionBodies(std::map<std::string, std::shared_ptr<GM::Element>>& motionBodies)
{
    using namespace Doc;
    QDomElement motionBodyParent = m_root.firstChildElement(MotionBodies);

    QDomNodeList motionBodiesList = motionBodyParent.elementsByTagName(MotionBody);

    for (int i = 0; i < motionBodiesList.size(); i++) {
        QDomNode item = motionBodiesList.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string name = element.attribute("name").toStdString();

            QDomElement origin = element.firstChildElement(Origin);

            double originX = origin.attribute("x").toDouble();
            double originY = origin.attribute("y").toDouble();

            auto motionBody = std::dynamic_pointer_cast<GM::MotionBody>(motionBodies[name]);
            //motionBody->setOrigin(QPointF(originX, originY));

            QDomElement boundingRect = element.firstChildElement("BoundingRect");

            double rectX = boundingRect.attribute("x").toDouble();
            double rectY = boundingRect.attribute("y").toDouble();
            double rectW = boundingRect.attribute("w").toDouble();
            double rectH = boundingRect.attribute("h").toDouble();

            motionBody->setBody(QRectF(rectX, rectY, rectW, rectH));

            updateColor(motionBody, element);
        }
    }
}

void SceneFromXML::updateJoints(std::map<std::string, std::shared_ptr<GM::Element>>& joints)
{
    using namespace Doc;
    QDomElement jointsParent = m_root.firstChildElement(Joints);

    QDomNodeList jointsList = jointsParent.elementsByTagName(Joint);

    for (int i = 0; i < jointsList.size(); i++) {
        QDomNode item = jointsList.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string name= element.attribute("name").toStdString();

            QDomElement action = element.firstChildElement(Action);

            double actionX = action.attribute("x").toDouble();
            double actionY = action.attribute("y").toDouble();

            QDomElement base = element.firstChildElement(Base);

            double baseX = base.attribute("x").toDouble();
            double baseY = base.attribute("y").toDouble();

            auto joint = std::dynamic_pointer_cast<GM::Joint>(joints[name]);

            joint->setBaseConnection(QPointF(baseX, baseY));
            joint->setActionConnection(QPointF(actionX, actionY));

            updateColor(joints[name], element);
        }
    }
}

void SceneFromXML::updateConnectors(std::map<std::string, std::shared_ptr<GM::Element>>& connectors)
{
    using namespace Doc;
    QDomElement connectorsParent = m_root.firstChildElement(Connectors);

    QDomNodeList connectorsList = connectorsParent.elementsByTagName(Connector);

    for (int i = 0; i < connectorsList.size(); i++) {
        QDomNode item = connectorsList.at(i);

        if (item.isElement()) {
            QDomElement element = item.toElement();

            std::string name = element.attribute("name").toStdString();

            QDomElement action = element.firstChildElement(Action);

            double actionX = action.attribute("x").toDouble();
            double actionY = action.attribute("y").toDouble();

            QDomElement base = element.firstChildElement(Base);

            double baseX = base.attribute("x").toDouble();
            double baseY = base.attribute("y").toDouble();

            auto connector = std::dynamic_pointer_cast<GM::Connector>(connectors[name]);

            connector->setBaseConnection(QPointF(baseX, baseY));
            connector->setActionConnection(QPointF(actionX, actionY));

            updateColor(connectors[name], element);
        }
    }
}

void SceneFromXML::updateColor(std::shared_ptr<GM::Element> graphicElement, const QDomElement& domElement)
{
    QDomElement tagColor = domElement.firstChildElement("Color");

    int red= tagColor.attribute("r").toInt();
    int green= tagColor.attribute("g").toInt();
    int blue= tagColor.attribute("b").toInt();
    int alpha= tagColor.attribute("a").toInt();

    QColor color(red,green,blue,alpha);
    graphicElement->setColor(color);
}
