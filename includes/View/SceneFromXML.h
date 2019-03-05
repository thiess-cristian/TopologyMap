#pragma once
#include <memory>
#include <qfile.h>
#include <qdom.h>
#include <GraphicMotionBody.h>

class GraphicMechanism;
class GraphicJoint;
class GraphicConnector;

class SceneFromXML
{
public:
    SceneFromXML(std::string modelName);

    void updateFromXML(std::shared_ptr<GraphicMechanism> mechanism, QFile & file);

private:

    void updateMotionBodies(std::shared_ptr<GraphicMechanism> mechanism);
    void updateJoints(std::map<std::string, GraphicJoint*> joints);
    void updateConnectors(std::map<std::string, GraphicConnector*> connectors);
    void updateColor(GraphicElement& graphicElement,const QDomElement& domElement);

    QDomDocument m_document;
    QDomElement m_root;
    std::string m_modelName;
};