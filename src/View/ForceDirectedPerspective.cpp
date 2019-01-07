#include "ForceDirectedPerspective.h"
#include "Mechanism.h"
#include "Point3D.h"

ForceDirectedPerspective::ForceDirectedPerspective(std::shared_ptr<Mechanism> mechanism, double width, double height):
    m_mechanism(mechanism),
    m_width(width),
    m_height(height),
    m_t(1000),
    m_iterations(900)
{

    m_k = sqrt(m_width*m_height / m_mechanism->getMotionBodies().size());

    for (const auto& motionBody : m_mechanism->getMotionBodies()) {
        m_graph2.addNode(motionBody.second);
    }

    for (const auto& joint : m_mechanism->getJoints()) {
        m_graph2.addEdge(joint.second);
    }

    for (const auto& connector : m_mechanism->getConnectors()) {
        m_graph2.addEdge(connector.second);
    }
   // m_graph2.forceDirectedLayout2(m_width, m_height);
    m_graph2.forceDirectedLayout3();
}

QPointF ForceDirectedPerspective::projectPoint(const Point3D & point) const
{
    return QPointF(point.getX(),point.getY());
}

QPointF ForceDirectedPerspective::projectMotionBody(const MotionBody & motionBody) const
{
    auto node = m_graph2.getNodeCoord(motionBody);
    return QPointF(node.x*500,node.y*500);
}

QPointF ForceDirectedPerspective::projectLinkAtachment(const Link & link, LinkType type) const
{
    auto motionbody = type == LinkType::Action ? link.getAction() : link.getBase();
    return projectMotionBody(motionbody);
}

void ForceDirectedPerspective::computeLayout()
{
    for (size_t i = 0; i < m_iterations; i++) {
        computeRepulsiveForces();
        computeAttractiveForces();
        setCoords();
        coolTemperature();
    }
}

void ForceDirectedPerspective::computeRepulsiveForces()
{
    for (const auto& nodeV : m_graph.getNodes()) {
        m_displacement[nodeV] = QPointF(0,0);

        for (const auto& nodeU : m_graph.getNodes()) {
            if (!(nodeU == nodeV)) {
                QPointF delta = projectPoint(nodeV.getOrigin()) - projectPoint(nodeU.getOrigin());
                double deltaNorm = sqrt(delta.rx()*delta.rx() + delta.ry()*delta.ry())+0.000001;
                m_displacement[nodeV] += delta / deltaNorm*fr(deltaNorm);
            }
        }
    }

}

void ForceDirectedPerspective::computeAttractiveForces()
{
    for (int i = 0; i < m_graph.getNodes().size()-1;i++) {
        auto nodeV = m_graph.getNodes()[i];
        for (auto j = i + 1; j < m_graph.getNodes().size(); j++) {
            auto nodeU = m_graph.getNodes()[j];
            if (m_graph.areNeighbors(nodeV, nodeU)) {
                QPointF delta = projectPoint(nodeV.getOrigin()) - projectPoint(nodeU.getOrigin());
                double deltaNorm = sqrt(delta.rx()*delta.rx() + delta.ry()*delta.ry());
                m_displacement[nodeV] -= delta / deltaNorm*fa(deltaNorm);
                m_displacement[nodeU] += delta / deltaNorm*fa(deltaNorm);
            }
        }
    }
}

void ForceDirectedPerspective::setCoords()
{
    for (auto& node : m_graph.getNodes()) {
        QPointF disp = m_displacement[node];
        double normDisp= sqrt(disp.rx()*disp.rx() + disp.ry()*disp.ry());
        QPointF pos = projectPoint(node.getOrigin()) + (disp / normDisp)*std::min(normDisp, m_t);
        double newX = std::min(m_width / 2, std::max(-m_width / 2, pos.rx()));
        double newY = std::max(m_height / 2, std::max(-m_height / 2, pos.ry()));

        m_graph.setNodeCoords(node, newX, newY);
    }
}

void ForceDirectedPerspective::coolTemperature()
{
    m_t *= 0.9;
}

double ForceDirectedPerspective::fr(double x)
{
    return (x*x) / m_k;
}

double ForceDirectedPerspective::fa(double x)
{
    return (m_k*m_k) / x;
}
