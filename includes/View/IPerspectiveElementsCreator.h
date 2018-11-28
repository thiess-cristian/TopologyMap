#pragma once
#include "Point3D.h"
#include <vector>
#include <memory>
#include <qpoint.h>

class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;
class Mechanism;


class IPerspectiveElementsCreator
{
public:
    virtual std::vector<GraphicMotionBody*> createMotionBodies() const;
    virtual std::vector<GraphicJoint*> createJoints() const;
    virtual std::vector<GraphicConnector*> createConnectors() const;

    virtual QPoint projectPoint(const Point3D& point) const = 0;

protected:
    std::shared_ptr<Mechanism> m_mechanism;
};