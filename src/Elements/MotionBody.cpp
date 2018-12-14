#include "MotionBody.h"
#include "LinkAtachment.h"
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
    m_linkAtachments.push_back(std::make_shared<LinkAtachment>(linkAtachment));
}

std::vector<std::shared_ptr<LinkAtachment>> MotionBody::getLinkAtachments() const
{
    return m_linkAtachments;
}

Point3D MotionBody::getOrigin() const
{
    return m_origin;
}
