#pragma once
#include "Link.h"
#include "XMLTagNames.h"

namespace DataModel
{
    class MotionBody;

    class Joint :public Link
    {
    public:
        Joint(const std::string& name,
              const JointType& type,
              std::shared_ptr<MotionBody> action,
              std::shared_ptr<MotionBody> base,
              const Point3D& actionConnection,
              const Point3D& baseConnection);
        Joint();

        JointType getType()const;

    protected:
        // Inherited via Element
        virtual bool isEqual(const Element & other) const override;

    private:
        JointType m_type;

    };
}