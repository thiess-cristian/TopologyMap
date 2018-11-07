#pragma once 
#include <vector>
#include <map>
#include <qdom.h>
#include <MotionBody.h>
#include <Joint.h>
#include <Connector.h>

#include <Mechanism.h>
#include <memory>
class QFile;

class DocumentParser
{
public:
    DocumentParser();
    ~DocumentParser();
   
    std::shared_ptr<Mechanism> createMechanism(QFile& file);

private:
    std::map<std::string, MotionBody> readMotionBodies();
    std::map<std::string, Joint> readJoints(const std::map<std::string, MotionBody>& m_motionBodies);
    std::map<std::string, Connector> readConnectors(const std::map<std::string, MotionBody>& m_motionBodies,const std::map<std::string, Joint>& m_joints);

    QDomDocument m_document;
    QDomElement m_root;
};