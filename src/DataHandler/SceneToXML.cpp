#include "DataHandler\SceneToXML.h"
#include <GraphicModel\Element.h>
#include <GraphicModel\Mechanism.h>
#include <GraphicModel\Joint.h>
#include <GraphicModel\Connector.h>
#include <GraphicModel\MotionBody.h>

#include <qcolor.h>
#include <qtextstream.h>

using namespace DataHandler;

SceneToXML::SceneToXML(std::string modelName):m_modelName(modelName)
{
    
}

void SceneToXML::writeToXml(std::shared_ptr<GM::Mechanism> mechanism, QFile & file)
{
    m_root = m_document.createElement("Elements");
    m_root.setAttribute("model_name", m_modelName.c_str());
    m_document.appendChild(m_root);

    writeMotionBodies(mechanism->getElements()[DataModel::ElementType::MotionBody]);
    writeJoints(mechanism->getElements()[DataModel::ElementType::Joint]);
    writeConnectors(mechanism->getElements()[DataModel::ElementType::Connector]);
    
    QTextStream output(&file);
    output << m_document.toString();
    file.close();
}

void SceneToXML::writeMotionBodies(const std::map<std::string, std::shared_ptr<GM::Element>>& motionBodies)
{
    QDomElement tagMotionBodies = m_document.createElement("MotionBodies");
    m_root.appendChild(tagMotionBodies);
    
    for (const auto& element : motionBodies) {
        auto graphicMotionBody = std::dynamic_pointer_cast<GM::MotionBody>(element.second);
        QDomElement tagMotionBody = m_document.createElement("MotionBody");

        tagMotionBody.setAttribute("name", element.first.c_str());
        tagMotionBodies.appendChild(tagMotionBody);

        QDomElement tagOrigin = m_document.createElement("Origin");

        tagOrigin.setAttribute("x", graphicMotionBody->boundingRect().center().x());
        tagOrigin.setAttribute("y", graphicMotionBody->boundingRect().center().y());

        tagMotionBody.appendChild(tagOrigin);

        QDomElement tagBoundingRect = m_document.createElement("BoundingRect");
        auto boundingRect = graphicMotionBody->boundingRect();

        tagBoundingRect.setAttribute("x", boundingRect.x());
        tagBoundingRect.setAttribute("y", boundingRect.y());
        tagBoundingRect.setAttribute("w", boundingRect.width());
        tagBoundingRect.setAttribute("h", boundingRect.height());

        tagMotionBody.appendChild(tagBoundingRect);

        addColorTag(element.second,tagMotionBody);
    }
}

void SceneToXML::writeJoints(const std::map<std::string, std::shared_ptr<GM::Element>>& joints)
{
    QDomElement tagJoints = m_document.createElement("Joints");
    m_root.appendChild(tagJoints);

    for (const auto& element : joints) {
        auto joint = std::dynamic_pointer_cast<GM::Joint>(element.second);
        QDomElement tagJoint = m_document.createElement("Joint");
        tagJoint.setAttribute("name", element.first.c_str());

        tagJoints.appendChild(tagJoint);

        QDomElement tagBase = m_document.createElement("Base");
        tagBase.setAttribute("x", joint->getBaseConnection().x());
        tagBase.setAttribute("y", joint->getBaseConnection().y());

        tagJoint.appendChild(tagBase);

        QDomElement tagAction = m_document.createElement("Action");
        tagAction.setAttribute("x", joint->getActionConnection().x());
        tagAction.setAttribute("y", joint->getActionConnection().y());

        tagJoint.appendChild(tagAction);

        addColorTag(element.second, tagJoint);
    }
}

void SceneToXML::writeConnectors(const std::map<std::string, std::shared_ptr<GM::Element>>& connectors)
{
    QDomElement tagConnectors=m_document.createElement("Connectors");
    m_root.appendChild(tagConnectors);

    for (const auto& element : connectors) {
        auto connector = std::dynamic_pointer_cast<GM::Connector>(element.second);
        QDomElement tagConnector = m_document.createElement("Connector");
        tagConnector.setAttribute("name", element.first.c_str());

        tagConnectors.appendChild(tagConnector);

        QDomElement tagBase = m_document.createElement("Base");
        tagBase.setAttribute("x", connector->getBaseConnection().x());
        tagBase.setAttribute("y", connector->getBaseConnection().y());

        tagConnector.appendChild(tagBase);

        QDomElement tagAction = m_document.createElement("Action");
        tagAction.setAttribute("x", connector->getActionConnection().x());
        tagAction.setAttribute("y", connector->getActionConnection().y());

        tagConnector.appendChild(tagAction);

        addColorTag(element.second, tagConnector);
    }
}

void SceneToXML::addColorTag(std::shared_ptr<GM::Element> graphicElement, QDomElement& domElement)
{
    QDomElement tagColor = m_document.createElement("Color");
    auto color = graphicElement->getColor();
    tagColor.setAttribute("r", color.red());
    tagColor.setAttribute("g", color.green());
    tagColor.setAttribute("b", color.blue());
    tagColor.setAttribute("a", color.alpha());

    domElement.appendChild(tagColor);
}
