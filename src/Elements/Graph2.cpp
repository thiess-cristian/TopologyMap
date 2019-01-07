#include "Graph2.h"
#include <iostream>
#include <set>

Graph2::Graph2():
m_t(1000),
m_iterations(7000)
{}

void Graph2::addNode(const MotionBody & node)
{
    m_nodes.push_back(new Node(node));
}

void Graph2::addEdge(const Link & edge)
{
    Node* action;
    Node* base;

    for (const auto& node : m_nodes) {
        if (node->obj == edge.getAction()) {
            action = node;
        }

        if (node->obj == edge.getBase()) {
            base = node;
        }
    }
    base->inc.push_back(action);
    action->inc.push_back(base);
}

Coord Graph2::getNodeCoord(const MotionBody & motionBody) const
{
    for (const auto& node : m_nodes) {
        if (node->obj == motionBody) {
            return node->pos;
        }
    }
}

void Graph2::forceDirectedLayout(double width, double height)
{
    m_width = width;
    m_height = height;
    m_k = sqrt(m_width*m_height / m_nodes.size());
    m_t = 10 * sqrt(m_nodes.size());

    for (size_t i = 0; i < m_iterations; i++) {
        computeRepulsiveForces();
        computeAttractiveForces();
        setCoords();
        coolTemperature(i);
        std::cout << i << std::endl;
    }
}

void Graph2::forceDirectedLayout2(double width, double height)
{
    m_t = 10 * sqrt(m_nodes.size());
    m_width = width;
    m_height = height;
    m_k = sqrt(m_width*m_height / m_nodes.size());


    for (auto &node:m_nodes) {
        std::set<Node*> s(node->inc.begin(), node->inc.end());
        node->inc.assign(s.begin(), s.end());
    }


    for (size_t it = 0; it < m_iterations; it++) {
    
        for (int v = 0; v < m_nodes.size(); v++) {
            auto nodeV = m_nodes[v];
            nodeV->disp = Coord();
            for (int u = v+1; u < m_nodes.size(); u++) {
                
                auto nodeU = m_nodes[u];

                Coord delta = nodeV->pos - nodeU->pos;

                double distance = delta.length()+0.0001;
                if (distance > 1000) {
                    continue;
                }

                double repulsion = m_k*m_k / distance;
                nodeV->disp += delta / distance*repulsion;
                nodeU->disp -= delta / distance*repulsion;
            }
        
            for (int u = 0; u < m_nodes.size(); u++) {

                if (v > u) {
                    continue;
                }
                auto nodeU = m_nodes[u];
                Coord delta = nodeV->pos - nodeU->pos;
                double distance = delta.length()+0.00001;
                double attraction = distance*distance / m_k;
                nodeV->disp -= delta / distance*attraction;
                nodeU->disp += delta / distance*attraction;
            }
        }
        for (int i = 0; i < m_nodes.size(); i++) {
            double dispNorm = m_nodes[i]->disp.length();

            if (dispNorm < 1.0) {
                continue;
            }

            double capDisp = std::min(dispNorm, m_t);

            auto disp = m_nodes[i]->disp / dispNorm*capDisp;
            m_nodes[i]->pos += disp;
      }

        if (m_t > 1.5) {
            m_t *= 0.85;
        } else {
            m_t = 1.5;
        }
    }
}

void Graph2::forceDirectedLayout3()
{
    for (auto &node : m_nodes) {
        std::set<Node*> s(node->inc.begin(), node->inc.end());
        node->inc.assign(s.begin(), s.end());
    }
    const double PI = 3.14159265358979323;
    for (int i = 0; i < m_nodes.size(); i++) {
        auto x = cos((2 * PI*i) / m_nodes.size());
        auto y = sin((2 * PI*i) / m_nodes.size());

        m_nodes[i]->pos.x = x;
        m_nodes[i]->pos.y = y;

    }

    const double k = 0.001;
    for (int iter = 0; iter < 10000; iter++) {
        for (size_t i = 0; i < m_nodes.size(); i++) {
            m_nodes[i]->disp.x = 0;
            m_nodes[i]->disp.y = 0;
        }
        std::cout << iter << std::endl;
        for (size_t i = 0; i < m_nodes.size() - 1; i++) {
            for (size_t j = i + 1; j < m_nodes.size(); j++) {
                double force = k / sqrt(pow(m_nodes[i]->pos.x - m_nodes[j]->pos.x, 2) +
                                        pow(m_nodes[i]->pos.y - m_nodes[j]->pos.y, 2));
                double theta = atan2((m_nodes[j]->pos.y - m_nodes[i]->pos.y),
                    (m_nodes[j]->pos.x - m_nodes[i]->pos.x));
                m_nodes[i]->disp.x -= force * cos(theta);
                m_nodes[i]->disp.y -= force * sin(theta);
                m_nodes[j]->disp.x += force * cos(theta);
                m_nodes[j]->disp.y += force * sin(theta);
            }
        }

        for (size_t i = 0; i < m_nodes.size(); i++) {
            for (size_t j = 0; j < m_nodes[i]->inc.size(); j++) {
                auto nodeV = m_nodes[i];
                auto nodeU = m_nodes[i]->inc[j];

                double force = k * (pow(nodeV->pos.x - nodeU->pos.x, 2)
                                    + pow(nodeV->pos.y - nodeU->pos.y, 2));
                double theta = atan2((nodeU->pos.y - nodeV->pos.y),
                    (nodeU->pos.x - nodeV->pos.x));

                // update net forces on nodes
                nodeV->disp.x += force * cos(theta);
                nodeV->disp.y += force * sin(theta);
                nodeU->disp.x -= force * cos(theta);
                nodeU->disp.y -= force * sin(theta);

            }
        }

        for (size_t i = 0; i < m_nodes.size(); i++) {
            if (m_nodes[i]->inc.size() != 0) {
                m_nodes[i]->pos.x += m_nodes[i]->disp.x;
                m_nodes[i]->pos.y += m_nodes[i]->disp.y;
            }
        }
    }
}

void Graph2::computeRepulsiveForces()
{
    for (auto& nodeV :m_nodes) {
        nodeV->disp = Coord(0, 0);

        for (const auto& nodeU : m_nodes) {
            if (!(nodeU->obj == nodeV->obj)) {
                Coord dist = nodeV->pos - nodeU->pos;
                double delta = dist.length()+0.00001;
                double d = fr(delta)/delta;
                nodeV->disp += dist*d;
            }
        }
    }
}

void Graph2::computeAttractiveForces()
{
    for (int i = 0; i < m_nodes.size() - 1; i++) {
        auto nodeV = m_nodes[i];
        for (auto j = 0; j < m_nodes.size(); j++) {
            auto nodeU = m_nodes[j];
            if (nodeV->isAdjacent(*nodeU)) {
                
                Coord dist = nodeV->pos - nodeU->pos;
                double delta = dist.length() + 0.00001;
                double d = fa(delta) / delta;
                nodeV->disp -= dist*d;
                nodeU->disp += dist*d;
                
            }
        }
    }
}

void Graph2::setCoords()
{
    for (auto& node : m_nodes) {
        Coord disp = node->disp;
        double normDisp = sqrt(disp.x*disp.x + disp.y*disp.y) + 0.000001;
        node->pos += disp.unit()*std::min(disp.length(), m_t);
        double newX = std::min(m_width / 2, std::max(-m_width / 2, node->pos.x));
        double newY = std::max(m_height / 2, std::max(-m_height / 2, node->pos.y));

       // node->pos.x = newX;
       // node->pos.y = newY;
    }
}

void Graph2::coolTemperature(double it)
{
    if (m_t > 1.5) {
        m_t *= 0.85;
    } else {
        m_t = 1.5;
    }
}
double Graph2::fr(double x)
{
    return (x*x) / m_k;
}

double Graph2::fa(double x)
{
    return (m_k*m_k) / x;
}

