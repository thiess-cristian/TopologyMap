#pragma once
#include "Point3D.h"
#include "LinkAtachment.h"
#include "MotionBody.h"
#include <vector>
#include <memory>
#include <qpoint.h>

class Mechanism;

class IPerspective
{
public:
    virtual QPointF projectPoint(const Point3D& point) const = 0;
    virtual QPointF projectMotionBody(const MotionBody& motionBody)const = 0;
    virtual QPointF projectLinkAtachment(const LinkAtachment& linkAtachment) const {
        return projectLinkAtachment(linkAtachment.getLink(), linkAtachment.getLinkType());
    };
    virtual QPointF projectLinkAtachment(const Link& link,LinkType type)const = 0;


};