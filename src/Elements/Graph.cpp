#include "Graph.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <set>
#include <chrono>

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
   
    makeCircle();
  
    auto start = std::chrono::steady_clock::now();

    while (!m_convergent) {
        
        resetDisplacement();
        calculateRepulsiveForces();
        calculateAttractiveForces();
        setNewPosition();
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);

    std::cout << duration.count();

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
        auto &nodeVPos = nodeV->pos;

        for (size_t j = i + 1; j < m_nodesSize; j++) {
    
            auto &nodeU = m_nodes[j];
            auto &nodeUPos = nodeU->pos;

            Coord displacement = (nodeVPos - nodeUPos);
            displacement = displacement * m_k / displacement.lengthSquared();
            nodeV->disp += displacement;
            nodeU->disp -= displacement;

        }
    }
}

void Graph::calculateAttractiveForces()
{

    for (size_t i = 0; i < m_nodesSize; i++) {

        auto &nodeV = m_nodes[i];
        auto &nodeVPos = nodeV->pos;

        for (size_t j = 0; j < nodeV->inc.size(); j++) {

            auto &nodeU = nodeV->inc[j];
            auto &nodeUPos = nodeU->pos;

            Coord displacement = (nodeVPos - nodeUPos) * m_k;
            nodeV->disp -= displacement;
            nodeU->disp += displacement;
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

