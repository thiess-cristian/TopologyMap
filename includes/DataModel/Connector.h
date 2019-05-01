#pragma once
#include "Link.h"
#include "Joint.h"
#include "XMLTagNames.h"
#include <memory>

namespace DataModel
{
    class MotionBody;

    class Connector :public Link
    {
    public:
        Connector(const ConnectorKind& kind,
                  const std::string& name,
                  const std::string& type,
                  std::shared_ptr<MotionBody> action,
                  std::shared_ptr<MotionBody> base,
                  const Point3D& actionConnection,
                  const Point3D& baseConnection);
        Connector(const ConnectorKind& kind, const std::string& name, const std::string& type, std::shared_ptr<Joint> joint);
        Connector();

        ConnectorKind getKind()const;

    private:
        ConnectorKind m_kind;
    };
}