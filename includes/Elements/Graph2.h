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

    double distance(const Coord& coord)
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

class Graph2
{
public:
    Graph2();
    void addNode(const MotionBody& node);
    void addEdge(const Link& edge);

    Coord getNodeCoord(const MotionBody& motionBody) const;

    void forceDirectedLayout(double width,double height);
    void forceDirectedLayout2(double width, double height);
    void forceDirectedLayout3();

private:
    void computeRepulsiveForces();
    void computeAttractiveForces();
    void setCoords();
    void coolTemperature(double it);

    double fr(double x);
    double fa(double x);

    double m_width;
    double m_height;
    double m_k;
    double m_t;
    size_t m_iterations;

    std::vector<Node*> m_nodes;
};