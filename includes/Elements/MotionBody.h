#pragma once
#include "Element.h"
#include "Point3D.h"
#include <qpoint.h>
#include <vector>
#include <memory>

class LinkAtachment;

class MotionBody :public Element
{
public:
    MotionBody(const std::string& name="", const Point3D& origin=Point3D());

    std::string getName() const;
    void addLinkAtachment(const LinkAtachment& linkAtachment);

    std::vector<std::shared_ptr<LinkAtachment>> getLinkAtachments()const;

    Point3D getOrigin()const;
    void setOrigin(const Point3D& point) const;

    bool operator==(const MotionBody& motionbody) const;
    bool operator<(const MotionBody& motionbody)const;

private:
    std::vector<std::shared_ptr<LinkAtachment>> m_linkAtachments;
    mutable Point3D m_origin;
};
