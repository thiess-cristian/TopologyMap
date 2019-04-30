#pragma once
#include "IPerspective.h"
#include "Graph.h"
#include "MotionBody.h"
#include <memory>
#include <qpoint.h>
#include <ForceDirectedLayout.h>
#include <Graph\Graph.h>

class Mechanism;

class ForceDirectedPerspective :public IPerspective
{
public: 
    ForceDirectedPerspective(std::shared_ptr<Mechanism> mechanism);

    // Inherited via IPerspective
    virtual QPointF projectPoint(const Point3D & point) const override;
    virtual QPointF projectMotionBody(const MotionBody & motionBody) const override;
    virtual QPointF projectLinkAtachment(const Link & link, LinkType type) const override;
private:

    std::shared_ptr<Mechanism> m_mechanism;
    
    Graph::Graph<MotionBody, double> graph;
};
