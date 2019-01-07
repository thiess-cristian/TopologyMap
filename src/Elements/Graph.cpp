#include "Graph.h"
#include "LinkAtachment.h"
#include <list>
#include <functional>

Graph::Graph()
{}

void Graph::addNode(const MotionBody & node)
{
    m_nodes[node] = {};
}

void Graph::addEdge(const Link & edge)
{
    m_nodes[edge.getAction()].push_back(edge.getBase());
    m_nodes[edge.getBase()].push_back(edge.getAction());
}

void Graph::addNodeNeighbors(const MotionBody & node,const std::vector<MotionBody>& neighbors)
{
    for (const auto& neighbor : neighbors) {
        m_nodes[node].push_back(neighbor);
    }
}

std::set<Link, Compare> Graph::getEdges() const
{
    std::set<Link, Compare> edges;

    for (const auto& node : m_nodes) {
        for (const auto& edge : node.second) {
            for (const auto& link : edge.getLinkAtachments()) {
                edges.emplace(link->getLink());
            }
        }
    }

    return edges;
}
std::vector<MotionBody> Graph::getNodes() const
{
    std::set <MotionBody, Compare> nodes;

    for (const auto& node : m_nodes) {
        nodes.emplace(node.first);
    }

    return std::vector<MotionBody>(nodes.begin(),nodes.end());
}


std::pair<MotionBody, MotionBody> Graph::getIncidentNodes(const Link & link) const
{
    return std::pair<MotionBody, MotionBody>(link.getAction(), link.getBase());
}

std::vector<MotionBody> Graph::getNeighbors(const MotionBody & motionBody) const
{
    return m_nodes.at(motionBody);
}

MotionBody Graph::getNode(const MotionBody & motionBody)const
{
    return m_nodes.find(motionBody)->first;
}

void Graph::removeNode(const MotionBody & motionBody)
{
    m_nodes.erase(motionBody);

    for (auto& node : m_nodes) {
        auto it = std::find(node.second.begin(), node.second.end(), motionBody);
        if (it != node.second.end()) {
            node.second.erase(it);
        }
    }
}

size_t Graph::nrOfNeighbors(const MotionBody & motionBody)
{
    return m_nodes[motionBody].size();
}

std::vector<Graph> Graph::split()
{
    std::list<MotionBody> notVisited;

    for (const auto& node : m_nodes) {
        notVisited.push_back(node.first);
    }

    std::vector<Graph> subGraphs;
    std::function<void(MotionBody node, Graph& sub)> dfs;

    dfs = [&dfs, &notVisited, this](MotionBody node, Graph& sub) {
        notVisited.remove(node);
        sub.addNode(node);
        sub.addNodeNeighbors(node, m_nodes[node]);
        for (const auto& neighbor : m_nodes[node]) {
            if (std::find(notVisited.begin(), notVisited.end(), neighbor) != notVisited.end()) {
                dfs(neighbor, sub);
            }
        }
    };

    while (!notVisited.empty()) {

        Graph subGraph;
        dfs(notVisited.front(), subGraph);
        subGraphs.push_back(subGraph);
    }

    return subGraphs;
}

std::vector<MotionBody> Graph::popLeaves()
{
    std::list<MotionBody> notVisited;

    for (const auto& node : m_nodes) {
        notVisited.push_back(node.first);
    }

    std::vector<MotionBody> leaves;

    std::function<void(MotionBody, std::vector<MotionBody>&)> dfs;

    dfs = [&dfs, &notVisited, this](MotionBody node, std::vector<MotionBody>& leaves) {
        notVisited.remove(node);
        if (nrOfNeighbors(node) > 1) {
            for (const auto& neighbor : m_nodes[node]) {
                if (std::find(notVisited.begin(), notVisited.end(), neighbor) != notVisited.end()) {
                    dfs(neighbor, leaves);
                }
            }
        }
        if (nrOfNeighbors(node) == 1) {
            removeNode(node);
            leaves.push_back(node);
        }
    };

    while (!notVisited.empty()) {
        dfs(notVisited.front(), leaves);
    }
    return leaves;
}

void Graph::setNodeCoords(const MotionBody & motionBody, double x, double y, double z)
{
    auto node = m_nodes.find(motionBody);
    node->first.setOrigin(Point3D(x, y, z));

    for (auto& node : m_nodes) {
        for (auto& ind : node.second) {
            if (ind == motionBody) {
                ind.setOrigin(Point3D(x, y, z));
            }
        }
    }
}

bool Graph::areNeighbors(const MotionBody & m1, const MotionBody & m2)
{
    return std::find(m_nodes[m1].begin(), m_nodes[m1].end(), m2) != m_nodes[m1].end();
}

