#pragma once
#include <memory>

namespace DataModel
{
    enum class LinkType
    {
        Action,
        Base
    };

    class Link;
    class MotionBody;

    class LinkAtachment
    {
    public:
        LinkAtachment(std::shared_ptr<Link> link, LinkType type);

        std::shared_ptr<Link> getLink()const;
        LinkType getLinkType()const;        
        std::shared_ptr<MotionBody> getMotionBody()const;

    private:        
        std::shared_ptr<Link> m_link;
        LinkType m_type;
    };
}