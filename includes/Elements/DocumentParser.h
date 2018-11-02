#pragma once 
#include <vector>
#include <map>
#include <qdom.h>
#include <MotionBody.h>
#include <Joint.h>
#include <Connector.h>

class QFile;

class DocumentParser
{
public:
    DocumentParser(QFile& file);
    ~DocumentParser();
    
    std::map<std::string, MotionBody> getMotionBodies()  const;
    std::map<std::string, Joint> getJoints() const;
    std::map<std::string, Connector> getConnectors() const;

private:
    void initMotionBodies();
    void initJoints();
    void initConnectors();

    QDomDocument m_document;
    QDomElement m_root;

    std::map<std::string, MotionBody> m_motionBodies;
    std::map<std::string, Joint> m_joints;
    std::map<std::string, Connector> m_connectors;

};