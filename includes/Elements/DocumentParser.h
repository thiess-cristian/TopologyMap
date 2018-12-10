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

enum class Version
{
    V_12,
    V_13
};

class DocumentParser
{
public:
    DocumentParser();
    ~DocumentParser();
   
    std::shared_ptr<Mechanism> createMechanism(QFile& file);

private:
    void readFileVersion();
    std::map<std::string, MotionBody> readMotionBodies();
    std::map<std::string, Joint> readJoints(std::map<std::string, MotionBody>& m_motionBodies);
    std::map<std::string, Connector> readConnectors(std::map<std::string, MotionBody>& m_motionBodies,const std::map<std::string, Joint>& m_joints);

    QDomDocument m_document;
    QDomElement m_root;

    Version m_version;

    std::map<Version, const char*> m_motionBodyName;
    std::map<Version, const char*> m_motionBodiesName;
    std::map<Version, const char*> m_selectedMotionBodyName;
};