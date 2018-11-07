#include "Mechanism.h"

Mechanism::Mechanism(const std::map<std::string, MotionBody>& motionBodies, 
                     const std::map<std::string, Joint>& joints, 
                     const std::map<std::string, Connector>& connectors):
    m_motionBodies(motionBodies),
    m_joints(joints),
    m_connectors(connectors)
{


}

std::map<std::string, MotionBody> Mechanism::getMotionBodies() const
{
    return m_motionBodies;
}

std::map<std::string, Joint> Mechanism::getJoints() const
{
    return m_joints;
}

std::map<std::string, Connector> Mechanism::getConnectors() const
{
    return m_connectors;
}
