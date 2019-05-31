#pragma once
#include "DataModel\Element.h"
#include "DataModel\Point3D.h"

#include <memory>


namespace DataModel
{
    class MotionBody;

    class Link :public Element
    {
    public:
        Link(const std::string& name,
             const std::string& type,
             std::shared_ptr<MotionBody> action,
             std::shared_ptr<MotionBody> base,
             const Point3D& actionConnection,
             const Point3D& baseConnection);

        std::shared_ptr<MotionBody> getAction()const;
        std::shared_ptr<MotionBody> getBase()const;
        Point3D getActionConnection() const;
        Point3D getBaseConnection() const;

    protected:
        // Inherited via Element
        virtual bool isEqual(const Element & other) const override;

        Point3D m_actionConnection;
        Point3D m_baseConnection;
        std::string type;
        std::shared_ptr<MotionBody> m_action;
        std::shared_ptr<MotionBody> m_base;

    };
}