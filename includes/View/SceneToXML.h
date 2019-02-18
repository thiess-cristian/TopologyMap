#pragma once
#include <memory>
#include <vector>
#include <qdom.h>
#include <qfile.h>

class GraphicMechanism;
class GraphicMotionBody;
class GraphicConnector;
class GraphicJoint;

class SceneToXML
{
public:
    SceneToXML();

    void writeToXml(std::shared_ptr<GraphicMechanism> mechanism, QFile & file);

private:
    void writeMotionBodies(const std::vector<GraphicMotionBody*>& motionBodies);
    
    QDomDocument m_document;
    QDomElement m_root;
    std::string m_filename;
};