#pragma once
#include "MotionBody.h"
#include "Link.h"
#include "Element.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include <utility>
#include <list>

struct Compare
{
    bool operator() (const Element& l, const Element& r) const
    {
        return l.getName() < r.getName();
    }
};

class Graph
{
public:
    Graph();

    void addNode(const MotionBody& node);
    void addEdge(const Link& edge);
    void addNodeNeighbors(const MotionBody& node,const std::vector<MotionBody>& neighbors);

    std::set<Link, Compare> getEdges()const;
    std::vector<MotionBody> getNodes()const;

    std::pair<MotionBody, MotionBody> getIncidentNodes(const Link& link) const;
    std::vector<MotionBody> getNeighbors(const MotionBody& motionBody) const;

    MotionBody getNode(const MotionBody& motionBody) const;

    void removeNode(const MotionBody& motionBody);
    size_t nrOfNeighbors(const MotionBody& motionBody);

    std::vector<Graph> split();

    std::vector<MotionBody> popLeaves();

    void setNodeCoords(const MotionBody& node, double x = 0, double y = 0, double z = 0);

    bool areNeighbors(const MotionBody& m1, const MotionBody& m2);
   
private:
    std::map<MotionBody, std::vector<MotionBody>, Compare> m_nodes;

};