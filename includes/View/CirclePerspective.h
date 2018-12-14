#pragma once
#include "IPerspective.h";
#include <memory>

class Mechanism;

class CirclePerspective :public IPerspective
{
public:
    CirclePerspective(std::shared_ptr<Mechanism> mechanism);

    // Inherited via IPerspective
    virtual QPointF projectPoint(const Point3D & point) const override;
    virtual QPointF projectMotionBody(const MotionBody & motionBody) const override;
    virtual QPointF projectLinkAtachment(const Link & link, LinkType type) const override;

private:
    std::shared_ptr<Mechanism> m_mechanism;
};


