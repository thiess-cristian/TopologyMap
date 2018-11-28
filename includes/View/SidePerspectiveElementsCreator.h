#pragma once
#include "IPerspectiveElementsCreator.h"
#include <memory>
#include <vector>

class Mechanism;
class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;

class SidePerspectiveElementsCreator :public IPerspectiveElementsCreator
{
public:
    SidePerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism);
    // Inherited via IPerspectiveElementsCreator
    virtual QPoint projectPoint(const Point3D & point) const override;
};