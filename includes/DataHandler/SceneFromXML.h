#pragma once
#include <memory>
#include <qfile.h>
#include <qdom.h>

namespace GM
{
    class Element;
    class Mechanism;
}

namespace DataHandler
{
    class SceneFromXML
    {
    public:
        SceneFromXML(std::string modelName);

        void updateFromXML(std::shared_ptr<GM::Mechanism> mechanism, QFile & file);

    private:

        void updateMotionBodies(std::map<std::string, std::shared_ptr<GM::Element>>& motionBodies);
        void updateJoints(std::map<std::string, std::shared_ptr<GM::Element>>& joints);
        void updateConnectors(std::map<std::string, std::shared_ptr<GM::Element>>& connectors);
        void updateColor(std::shared_ptr<GM::Element> graphicElement, const QDomElement& domElement);

        QDomDocument m_document;
        QDomElement m_root;
        std::string m_modelName;
    };
}