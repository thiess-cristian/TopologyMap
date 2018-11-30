#pragma once
#include "IPerspective.h"
#include <memory>
#include <vector>

class SidePerspective :public IPerspective
{
public:
    SidePerspective(double scaleFactor = 1);
    // Inherited via IPerspectiveElementsCreator
    virtual QPointF projectPoint(const Point3D & point) const override;
};