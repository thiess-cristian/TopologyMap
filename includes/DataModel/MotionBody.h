#pragma once
#include "Element.h"
#include "Point3D.h"
#include "LinkAtachment.h"
#include <vector>
#include <memory>

namespace DataModel
{
    class LinkAtachment;

    class MotionBody :public Element
    {
    public:
        MotionBody(const std::string& name = "", const Point3D& origin = Point3D());

        std::string getName() const;
        void addLinkAtachment(const LinkAtachment& linkAtachment);

        std::vector<LinkAtachment> getLinkAtachments()const;

        Point3D getOrigin()const;
        void setOrigin(const Point3D& point) const;

        bool operator<(const MotionBody& motionbody)const;

    protected:
        // Inherited via Element
        virtual bool isEqual(const Element & other) const override;

    private:
        std::vector<LinkAtachment> m_linkAtachments;
        mutable Point3D m_origin;


    };
}