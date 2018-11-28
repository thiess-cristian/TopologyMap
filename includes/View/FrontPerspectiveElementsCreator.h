#pragma once
#include "IPerspectiveElementsCreator.h"
#include <memory>
#include <vector>

class Mechanism;
class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;

class FrontPerspectiveElementsCreator :public IPerspectiveElementsCreator
{
public:
    FrontPerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism);
    virtual QPoint projectPoint(const Point3D& point) const override;
};