#include "SceneToXML.h"
#include "GraphicMechanism.h"
#include "GraphicMotionBody.h"

#include <qtextstream.h>

SceneToXML::SceneToXML()
{
    
}

void SceneToXML::writeToXml(std::shared_ptr<GraphicMechanism> mechanism,QFile & file)
{
    m_root = m_document.createElement("Elements");
    m_document.appendChild(m_root);

    writeMotionBodies(mechanism->getGraphicMotionBodies());
    
    QTextStream output(&file);
    output << m_document.toString();
    file.close();
}

void SceneToXML::writeMotionBodies(const std::vector<GraphicMotionBody*>& motionBodies)
{
    QDomElement tagMotionBodies = m_document.createElement("MotionBodies");
    m_root.appendChild(tagMotionBodies);


    for (const auto& graphicMotionBody : motionBodies) {
        QDomElement tagMotionBody = m_document.createElement("MotionBody");
        tagMotionBodies.appendChild(tagMotionBody);

        QDomElement tagName = m_document.createElement("Name");
        tagMotionBody.appendChild(tagName);

        QDomText textName = m_document.createTextNode(graphicMotionBody->getModel().getName().c_str());
        tagName.appendChild(textName);

        QDomElement tagOrigin = m_document.createElement("Origin");

        tagOrigin.setAttribute("x", graphicMotionBody->getOrigin().x());
        tagOrigin.setAttribute("y", graphicMotionBody->getOrigin().y());

        tagMotionBody.appendChild(tagOrigin);
    }
}
