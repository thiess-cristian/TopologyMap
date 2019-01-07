#pragma once
#include "IPerspective.h"
#include "Graph.h"
#include "Graph2.h"
#include "MotionBody.h"
#include <memory>
#include <qpoint.h>

class Mechanism;

class ForceDirectedPerspective :public IPerspective
{
public: 
    ForceDirectedPerspective(std::shared_ptr<Mechanism> mechanism,double width,double height);

    // Inherited via IPerspective
    virtual QPointF projectPoint(const Point3D & point) const override;
    virtual QPointF projectMotionBody(const MotionBody & motionBody) const override;
    virtual QPointF projectLinkAtachment(const Link & link, LinkType type) const override;

    void computeLayout();
private:

    void computeRepulsiveForces();
    void computeAttractiveForces();
    void setCoords();
    void coolTemperature();

    double fr(double x);
    double fa(double x);

    std::shared_ptr<Mechanism> m_mechanism;

    Graph m_graph;
    Graph2 m_graph2;

    double m_width;
    double m_height;
    double m_k;
    double m_t;
    size_t m_iterations;

    std::map<MotionBody, QPointF> m_displacement;
};
