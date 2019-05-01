#include "DataModel\MotionBodyComponent.h"
#include "DataModel\MotionBody.h"

using namespace DataModel;

MotionBodyComponent::MotionBodyComponent(const std::string & name):Element(name)
{}

void MotionBodyComponent::addMotionBody(std::shared_ptr<MotionBody> motionBody)
{
    m_motionBodies[motionBody->getName()] = motionBody;
}
