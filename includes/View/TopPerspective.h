#pragma once
#include "IPerspective.h"
#include <memory>
#include <vector>

class TopPerspective:public IPerspective
{
public:
    TopPerspective();
    // Inherited via IPerspectiveElementsCreator
    virtual QPointF projectPoint(const Point3D & point) const override;
};