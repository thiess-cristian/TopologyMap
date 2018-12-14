#include "LinkAtachment.h"

LinkAtachment::LinkAtachment(const Link & link, LinkType type):m_link(link),m_type(type)
{
    
}

Link LinkAtachment::getLink() const
{
    return m_link;
}

LinkType LinkAtachment::getLinkType() const
{
    return m_type;
}

MotionBody LinkAtachment::getMotionBody() const
{
    return m_type == LinkType::Action ? m_link.getAction() : m_link.getBase();
}
