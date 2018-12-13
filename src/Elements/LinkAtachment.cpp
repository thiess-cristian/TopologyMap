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
