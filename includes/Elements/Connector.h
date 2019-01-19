#pragma once
#include "Link.h"
#include "Joint.h"
#include "XMLTagNames.h"

class Connector:public Link
{
public:
    Connector(const ConnectorKind& kind,
              const std::string& name,
              const std::string& type,
              const MotionBody& action,
              const MotionBody& base,
              const Point3D& actionConnection,
              const Point3D& baseConnection);
    Connector(const ConnectorKind& kind, const std::string& name, const std::string& type, const Joint& joint);
    Connector();

    ConnectorKind getKind()const;

private:
    ConnectorKind m_kind;
};