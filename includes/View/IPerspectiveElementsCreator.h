#pragma once
#include <vector>

class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;


class IPerspectiveElementsCreator
{
public:
    virtual std::vector<GraphicMotionBody*> createMotionBodies() const = 0;
    virtual std::vector<GraphicJoint*> createJoints() const = 0;
    virtual std::vector<GraphicConnector*> createConnectors() const = 0;
};