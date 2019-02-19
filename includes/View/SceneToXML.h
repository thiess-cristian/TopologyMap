#pragma once
#include <memory>
#include <vector>
#include <qdom.h>
#include <qfile.h>
#include <map>

class GraphicMechanism;
class GraphicMotionBody;
class GraphicConnector;
class GraphicJoint;

class SceneToXML
{
public:
    SceneToXML(std::string modelName);

    void writeToXml(std::shared_ptr<GraphicMechanism> mechanism, QFile & file);

private:
    void writeMotionBodies(const std::map<std::string,GraphicMotionBody*>& motionBodies);
    void writeJoints(const std::map<std::string, GraphicJoint*>& joints);
    void writeConnectors(const std::map<std::string, GraphicConnector*>& connectors);
    
    
    QDomDocument m_document;
    QDomElement m_root;
    std::string m_modelName;
};