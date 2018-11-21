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

    // Inherited via IPerspectiveElementsCreator
    virtual std::vector<GraphicMotionBody*> createMotionBodies() const override;
    virtual std::vector<GraphicJoint*> createJoints() const override;
    virtual std::vector<GraphicConnector*> createConnectors() const override;

private:
    std::shared_ptr<Mechanism> m_mechanism;
};