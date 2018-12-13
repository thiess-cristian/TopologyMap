#pragma once
#include "IPerspective.h"
#include <memory>
#include <vector>

class SidePerspective :public IPerspective
{
public:
    SidePerspective();
    // Inherited via IPerspectiveElementsCreator
    virtual QPointF projectPoint(const Point3D & point) const override;
    virtual QPointF projectMotionBody(const MotionBody & motionBody) const override;
    virtual QPointF projectLinkAtachment(const Link & link, LinkType type) const override;
};