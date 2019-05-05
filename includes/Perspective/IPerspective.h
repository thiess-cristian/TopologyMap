#pragma once
#include <DataModel\Point3D.h>
#include <DataModel\LinkAtachment.h>
#include <DataModel\Link.h>
#include <DataModel\MotionBody.h>
#include <qpoint.h>


namespace Perspective
{
    class IPerspective
    {
    public:
        virtual QPointF projectPoint(const DataModel::Point3D& point) const = 0;
        virtual QPointF projectMotionBody(const DataModel::MotionBody& motionBody)const = 0;
        virtual QPointF projectLinkAtachment(const DataModel::Link& link, DataModel::LinkType type)const = 0;

        virtual QPointF projectLinkAtachment(const DataModel::LinkAtachment& linkAtachment) const
        {
            return projectLinkAtachment(*(linkAtachment.getLink()), linkAtachment.getLinkType());
        };
    };
}