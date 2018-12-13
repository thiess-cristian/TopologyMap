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
    MotionBody type;
    switch (m_type) {
        case LinkType::Action:{
            type = m_link.getAction();
            break;
        }
        case LinkType::Base: {
            type = m_link.getBase();
            break;
        }
        default:
            break;
    }
    return type;
}
