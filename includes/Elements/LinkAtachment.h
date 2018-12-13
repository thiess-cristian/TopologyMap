#pragma once

#include "Link.h"

enum class LinkType
{
    Action,
    Base
};

class LinkAtachment
{
public:
    LinkAtachment(const Link& link,LinkType type);

    Link getLink()const;
    LinkType getLinkType()const;

private:
    Link m_link;
    LinkType m_type;
};