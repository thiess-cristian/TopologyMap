#pragma once

#include "MotionBody.h"
#include "Joint.h"
#include "Connector.h"
#include <map>
#include <string>

class Mechanism
{
public:
    Mechanism(const std::map<std::string, MotionBody>& motionBodies, 
              const std::map<std::string, Joint>& joints, 
              const std::map<std::string, Connector>& connectors);

    std::map<std::string, MotionBody> getMotionBodies() const;
    std::map<std::string, Joint> getJoints() const;
    std::map<std::string, Connector> getConnectors() const;

private:

    std::map<std::string, MotionBody> m_motionBodies;
    std::map<std::string, Joint> m_joints;
    std::map<std::string, Connector> m_connectors;

};