#include "DataModel\MotionBody.h"
#include "DataModel\LinkAtachment.h"

using namespace DataModel;

MotionBody::MotionBody(const std::string& name,const Point3D& origin):
    Element(name),
    m_origin(origin),
    m_linkAtachments()
{

}

std::string MotionBody::getName() const
{
    return m_name;
}

void MotionBody::addLinkAtachment(const LinkAtachment & linkAtachment)
{
    m_linkAtachments.push_back(linkAtachment);
}

std::vector<LinkAtachment> MotionBody::getLinkAtachments() const
{
    return m_linkAtachments;
}

Point3D MotionBody::getOrigin() const
{
    return m_origin;
}

void MotionBody::setOrigin(const Point3D & point) const
{
    m_origin = point;
}

bool MotionBody::operator==(const MotionBody & motionbody) const
{
    return m_name == motionbody.m_name;
}

bool MotionBody::operator<(const MotionBody & motionbody) const
{
    return m_name < motionbody.m_name;
}

