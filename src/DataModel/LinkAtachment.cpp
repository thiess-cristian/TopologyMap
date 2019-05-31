#include "DataModel\LinkAtachment.h"
#include "DataModel\Link.h"

using namespace DataModel;

LinkAtachment::LinkAtachment(std::shared_ptr<Link> link, LinkType type):m_link(link),m_type(type)
{}

std::shared_ptr<Link> LinkAtachment::getLink() const
{
    return m_link;
}

LinkType LinkAtachment::getLinkType() const
{
    return m_type;
}

std::shared_ptr<MotionBody> LinkAtachment::getMotionBody() const
{
    return m_type == LinkType::Action ? m_link->getAction() : m_link->getBase();
}

bool LinkAtachment::operator==(const LinkAtachment & other) const
{
    return m_type == other.m_type && *m_link == *other.m_link;
}
