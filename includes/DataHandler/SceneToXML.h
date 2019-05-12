#pragma once
#include <memory>
#include <vector>
#include <qdom.h>
#include <qfile.h>
#include <map>

namespace GM
{
    class Element;
    class Mechanism;
}

namespace DataHandler
{
    class SceneToXML
    {
    public:
        SceneToXML(std::string modelName);

        void writeToXml(std::shared_ptr<GM::Mechanism> mechanism, QFile & file);

    private:
        void writeMotionBodies(const std::map<std::string, std::shared_ptr<GM::Element>>& motionBodies);
        void writeJoints(const std::map<std::string, std::shared_ptr<GM::Element>>& joints);
        void writeConnectors(const std::map<std::string, std::shared_ptr<GM::Element>>& connectors);
        void addColorTag(std::shared_ptr<GM::Element> graphicElement, QDomElement& domElement);

        QDomDocument m_document;
        QDomElement m_root;
        std::string m_modelName;
    };
}