#pragma once
#include "IPerspective.h";
#include <memory>

namespace DataModel
{
    class Mechanism;
}

namespace Perspective
{
    class CirclePerspective :public IPerspective
    {
    public:
        CirclePerspective(std::shared_ptr<DataModel::Mechanism> mechanism);

        // Inherited via IPerspective
        virtual QPointF projectPoint(const DataModel::Point3D & point) const override;
        virtual QPointF projectMotionBody(const DataModel::MotionBody & motionBody) const override;
        virtual QPointF projectLinkAtachment(const DataModel::Link & link, DataModel::LinkType type) const override;

    private:
        std::shared_ptr<DataModel::Mechanism> m_mechanism;
    };
}
