#include "SceneToXML.h"
#include "GraphicMechanism.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

#include <qtextstream.h>

SceneToXML::SceneToXML(std::string modelName):m_modelName(modelName)
{
    
}

void SceneToXML::writeToXml(std::shared_ptr<GraphicMechanism> mechanism, QFile & file)
{
    m_root = m_document.createElement("Elements");
    m_root.setAttribute("model_name", m_modelName.c_str());
    m_document.appendChild(m_root);

    writeMotionBodies(mechanism->getGraphicMotionBodies());
    writeJoints(mechanism->getGraphicJoints());
    writeConnectors(mechanism->getGraphicConnectors());
    
    QTextStream output(&file);
    output << m_document.toString();
    file.close();
}

void SceneToXML::writeMotionBodies(const std::map<std::string, GraphicMotionBody*>& motionBodies)
{
    QDomElement tagMotionBodies = m_document.createElement("MotionBodies");
    m_root.appendChild(tagMotionBodies);
    
    for (const auto& graphicMotionBody : motionBodies) {
        QDomElement tagMotionBody = m_document.createElement("MotionBody");

        tagMotionBody.setAttribute("name", graphicMotionBody.first.c_str());
        tagMotionBodies.appendChild(tagMotionBody);

        QDomElement tagOrigin = m_document.createElement("Origin");

        tagOrigin.setAttribute("x", graphicMotionBody.second->getOrigin().x());
        tagOrigin.setAttribute("y", graphicMotionBody.second->getOrigin().y());

        tagMotionBody.appendChild(tagOrigin);

        QDomElement tagBoundingRect = m_document.createElement("BoundingRect");
        auto boundingRect = graphicMotionBody.second->boundingRect();

        tagBoundingRect.setAttribute("x", boundingRect.x());
        tagBoundingRect.setAttribute("y", boundingRect.y());
        tagBoundingRect.setAttribute("w", boundingRect.width());
        tagBoundingRect.setAttribute("h", boundingRect.height());

        tagMotionBody.appendChild(tagBoundingRect);
    }
}

void SceneToXML::writeJoints(const std::map<std::string, GraphicJoint*>& joints)
{
    QDomElement tagJoints = m_document.createElement("Joints");
    m_root.appendChild(tagJoints);

    for (const auto& joint : joints) {
        QDomElement tagJoint = m_document.createElement("Joint");
        tagJoint.setAttribute("name", joint.first.c_str());

        tagJoints.appendChild(tagJoint);

        QDomElement tagBase = m_document.createElement("Base");
        tagBase.setAttribute("x", joint.second->getBaseConnection().x());
        tagBase.setAttribute("y", joint.second->getBaseConnection().y());

        tagJoint.appendChild(tagBase);

        QDomElement tagAction = m_document.createElement("Action");
        tagAction.setAttribute("x", joint.second->getActionConnection().x());
        tagAction.setAttribute("y", joint.second->getActionConnection().y());

        tagJoint.appendChild(tagAction);
    }
}

void SceneToXML::writeConnectors(const std::map<std::string, GraphicConnector*>& connectors)
{
    QDomElement tagConnectors=m_document.createElement("Connectors");
    m_root.appendChild(tagConnectors);

    for (const auto& connector : connectors) {
        QDomElement tagConnector = m_document.createElement("Connector");
        tagConnector.setAttribute("name", connector.first.c_str());

        tagConnectors.appendChild(tagConnector);

        QDomElement tagBase = m_document.createElement("Base");
        tagBase.setAttribute("x", connector.second->getBaseConnection().x());
        tagBase.setAttribute("y", connector.second->getBaseConnection().y());

        tagConnector.appendChild(tagBase);

        QDomElement tagAction = m_document.createElement("Action");
        tagAction.setAttribute("x", connector.second->getActionConnection().x());
        tagAction.setAttribute("y", connector.second->getActionConnection().y());

        tagConnector.appendChild(tagAction);
    }
}