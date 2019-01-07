#include "Graph.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <set>

Graph::Graph()
{}

void Graph::addNode(const MotionBody & node)
{
    m_nodes.push_back(new Node(node));
}

void Graph::addEdge(const Link & edge)
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

Coord Graph::getNodeCoord(const MotionBody & motionBody) const
{
    for (const auto& node : m_nodes) {
        if (node->obj == motionBody) {
            return node->pos;
        }
    }
}

void Graph::forceDirectedLayout()
{
    for (auto &node : m_nodes) {
        std::set<Node*> s(node->inc.begin(), node->inc.end());
        node->inc.assign(s.begin(), s.end());
    }

    m_nodesSize = m_nodes.size();
    /*
    for (int i = 0; i < m_nodes.size(); i++) {
        auto x = cos((2 * M_PI*i) / m_nodes.size());
        auto y = sin((2 * M_PI*i) / m_nodes.size());

        m_nodes[i]->pos.x = x;
        m_nodes[i]->pos.y = y;

    }

    const double m_k = 0.001;
    for (int iter = 0; iter < 10000; iter++) {
        for (size_t i = 0; i < m_nodes.size(); i++) {
            m_nodes[i]->disp.x = 0;
            m_nodes[i]->disp.y = 0;
        }
        std::cout << iter << std::endl;
        for (size_t i = 0; i < m_nodes.size() - 1; i++) {
            for (size_t j = i + 1; j < m_nodes.size(); j++) {
                double force = m_k / sqrt(pow(m_nodes[i]->pos.x - m_nodes[j]->pos.x, 2) +
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

                double force = m_k * (pow(nodeV->pos.x - nodeU->pos.x, 2)
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
    */

    makeCircle();
    /*
    for (int iter = 0; iter < 10000; iter++) {
        std::cout << iter << std::endl;
        resetDisplacement();
        calculateRepulsiveForces();
        calculateAttractiveForces();
        setNewPosition();
    }
    */

    int iter = 0;
    while (!m_convergent) {
        std::cout << iter++ << std::endl;
        resetDisplacement();
        calculateRepulsiveForces();
        calculateAttractiveForces();
        setNewPosition();
    }

}

void Graph::makeCircle()
{
    for (int i = 0; i < m_nodesSize; i++) {
        auto x = cos((2 * M_PI*i) / m_nodesSize);
        auto y = sin((2 * M_PI*i) / m_nodesSize);

        m_nodes[i]->pos = Coord(x, y);
    }
}

void Graph::resetDisplacement()
{
    for (size_t i = 0; i < m_nodesSize; i++) {
        m_nodes[i]->disp = Coord(0,0);
    }
}

void Graph::calculateRepulsiveForces()
{
    for (size_t i = 0; i < m_nodesSize - 1; i++) {

        auto &nodeV = m_nodes[i];
        const auto &nodeVPos = nodeV->pos;

        for (size_t j = i + 1; j < m_nodesSize; j++) {
    
            auto &nodeU = m_nodes[j];
            const auto &nodeUPos = nodeU->pos;

            double force = m_k / nodeVPos.distance(nodeUPos);
            double theta = atan2((nodeUPos.y - nodeVPos.y),(nodeUPos.x - nodeVPos.x));

            Coord displacement(cos(theta),sin(theta));

            nodeV->disp -= displacement*force;
            nodeU->disp += displacement*force;
        }
    }
}

void Graph::calculateAttractiveForces()
{

    for (size_t i = 0; i < m_nodesSize; i++) {

        auto &nodeV = m_nodes[i];
        const auto &nodeVPos = nodeV->pos;

        for (size_t j = 0; j < nodeV->inc.size(); j++) {

            auto &nodeU = nodeV->inc[j];
            const auto &nodeUPos = nodeU->pos;

            double force = m_k * nodeVPos.distance(nodeUPos);
            double theta = atan2((nodeUPos.y - nodeVPos.y),(nodeUPos.x - nodeVPos.x));

            Coord displacement(cos(theta), sin(theta));

            nodeV->disp += displacement*force;
            nodeU->disp -= displacement*force;
        }
    }
}

void Graph::setNewPosition()
{
    double maxDistance = -DBL_MIN;

    for (size_t i = 0; i < m_nodesSize; i++) {
        if (m_nodes[i]->inc.size() != 0) {

            auto curentPos = m_nodes[i]->pos;

            m_nodes[i]->pos += m_nodes[i]->disp;

            if (curentPos.distance(m_nodes[i]->pos) >maxDistance) {
                maxDistance = curentPos.distance(m_nodes[i]->pos);
            }
        }
    }

    if (maxDistance < m_e) {
        m_convergent = true;
    }

}

