#pragma once
#include "IPerspective.h"
#include <memory>
#include <vector>

class FrontPerspective :public IPerspective
{
public:
    FrontPerspective(double scaleFactor=1);
    virtual QPointF projectPoint(const Point3D& point) const override;
};