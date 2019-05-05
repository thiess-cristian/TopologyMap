#pragma once
#include "IPerspective.h"

namespace Perspective
{
    class SidePerspective :public IPerspective
    {
    public:
        SidePerspective();
        virtual QPointF projectPoint(const  DataModel::Point3D & point) const override;
        virtual QPointF projectMotionBody(const  DataModel::MotionBody & motionBody) const override;
        virtual QPointF projectLinkAtachment(const  DataModel::Link & link, DataModel::LinkType type) const override;
    };
}
