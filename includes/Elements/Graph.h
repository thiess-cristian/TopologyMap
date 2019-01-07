#pragma once
#include <vector>
#include <MotionBody.h>
#include <Link.h>
#include <random>

struct Coord
{
    Coord(double dx=0,double dy=0):x(dx),y(dy){}
    double x;
    double y;


    double length()
    {
        return sqrt(x*x + y*y);
    }

    double distance(const Coord& coord) const
    {
        return sqrt((x - coord.x)*(x - coord.x) + (y - coord.y)*(y - coord.y));
    }

    Coord unit()
    {
        double length = sqrt(x*x + y*y);
        if (length == 0) {
            return Coord(0.00001, 0.00001);
        } else {
            return Coord(x / length, y / length);
        }
    }

    Coord operator-(const Coord& coord)
    {
        return Coord(x - coord.x, y - coord.y);
    }

    Coord operator/(double d)
    {
        return Coord(x / d, y / d);
    }
    Coord operator*(double d)
    {
        return Coord(x*d, y*d);
    }

    Coord& operator+=(const Coord& coord)
    {
        x += coord.x;
        y += coord.y;
        return *this;
    }
    Coord& operator-=(const Coord& coord)
    {
        x -= coord.x;
        y -= coord.y;
        return *this;
    }
};


struct Node
{
    Node(const MotionBody& motionBody) :obj(motionBody) ,pos(motionBody.getOrigin().getX(), motionBody.getOrigin().getY()){
        pos.x = rand() % 10;
        pos.y = rand() % 10;
    }
    bool isAdjacent(const Node& node)
    {
        for (const auto& n : inc) {
            if (n->obj == node.obj) {
                return true;
            }
        }
        return false;
    }
    MotionBody obj;
    std::vector<Node*> inc;

    Coord disp;
    Coord pos;

};

class Graph
{
public:
    Graph();
    void addNode(const MotionBody& node);
    void addEdge(const Link& edge);

    Coord getNodeCoord(const MotionBody& motionBody) const;

    void forceDirectedLayout();
private:
    void makeCircle();
    void resetDisplacement();
    void calculateRepulsiveForces();
    void calculateAttractiveForces();
    void setNewPosition();

    std::vector<Node*> m_nodes;

    size_t m_nodesSize;
    const double m_k = 0.01;
    const double m_e = 0.001;
    bool m_convergent = false;

};