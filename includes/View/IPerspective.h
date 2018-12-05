#pragma once
#include "Point3D.h"
#include <vector>
#include <memory>
#include <qpoint.h>

class Mechanism;

class IPerspective
{
public:
    virtual QPointF projectPoint(const Point3D& point) const = 0;

protected:
    std::shared_ptr<Mechanism> m_mechanism;
};