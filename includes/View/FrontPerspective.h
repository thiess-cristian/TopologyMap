#pragma once
#include "IPerspective.h"
#include <memory>
#include <vector>

class FrontPerspective :public IPerspective
{
public:
    FrontPerspective();
    virtual QPointF projectPoint(const Point3D& point) const override;
};