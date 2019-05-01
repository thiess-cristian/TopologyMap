#pragma once
#include <iostream>
#include <memory>

#include <MotionBody.h>
#include <Graph.h>
#include <Joint.h>
#include <Connector.h>

#include <GraphCoord.h>
#include <GraphNode.h>
#include <Graph\Graph.h>
#include <Graph\ForceDirectedLayout.h>

#include<DataModel\Mechanism.h>
#include<DataModel\Joint.h>
#include<DataModel\MotionBody.h>
#include<DataModel\Connector.h>

void graphTest()
{
    //Point3D origin;

    //MotionBody m1("m1", origin);
    //MotionBody m2("m2", origin);
    //MotionBody m3("m3", origin);

    //MotionBody m4("m4", origin);
    //MotionBody m5("m5", origin);
    //MotionBody m6("m6", origin);

    //MotionBody m7("m7", origin);
    //MotionBody m8("m8", origin);
    //MotionBody m9("m9", origin);

    //MotionBody m10("m10", origin);
    //MotionBody m11("m11", origin);
    //MotionBody m12("m12", origin);
    ///*
    //MotionBody m1c(m1);
    //MotionBody m2c(m2);

    //Joint j1("j1", "t1", m1, m2, origin, origin);
    //Connector c1("k1","j2","t2",m3,m4, origin, origin);

    //Connector c1c(c1);

    //Graph g;

    //g.addNode(m1);
    //g.addNode(m2);
    //g.addNode(m3);
    //g.addNode(m4);

    //g.addEdge(j1);
    //g.addEdge(c1);

    //auto neighbors = g.getNeighbors(m1c);
    //auto inc = g.getIncidentNodes(c1c);
    //*/

    //Joint j1("j1", "t1", m1, m2, origin, origin);
    //Joint j2("j2", "t2", m2, m3, origin, origin);
    //Joint j3("j3", "t3", m3, m1, origin, origin);

    //Joint j4("j4", "t1", m4, m5, origin, origin);
    //Joint j5("j5", "t2", m5, m6, origin, origin);
    //Joint j6("j6", "t3", m6, m4, origin, origin);

    //Joint j7("j7", "t1", m7, m8, origin, origin);
    //Joint j8("j8", "t2", m8, m9, origin, origin);
    //Joint j9("j9", "t3", m9, m7, origin, origin);

    ////leaves
    //Joint j10("j10", "t3", m1, m10, origin, origin);
    //Joint j11("j11", "t3", m10, m11, origin, origin);


    //Graph g;

    //g.addNode(m1);
    //g.addNode(m2);
    //g.addNode(m3);
    //g.addNode(m4);
    //g.addNode(m5);
    //g.addNode(m6);
    //g.addNode(m7);
    //g.addNode(m8);
    //g.addNode(m9);
    //g.addNode(m10);
    //g.addNode(m11);

    //g.addEdge(j1);
    //g.addEdge(j2);
    //g.addEdge(j3);
    //g.addEdge(j4);
    //g.addEdge(j5);
    //g.addEdge(j6);
    //g.addEdge(j7);
    //g.addEdge(j8);
    //g.addEdge(j9);
    //g.addEdge(j10);
    //g.addEdge(j11);

    //auto subs = g.split();

    //auto leaves = g.popLeaves();
}

void graph2Test()
{
    /*
    Graph g;

    Point3D origin;

    MotionBody m1("m1", origin);
    MotionBody m2("m2", origin);
    MotionBody m3("m3", origin);

    MotionBody m4("m4", origin);
    MotionBody m5("m5", origin);
    MotionBody m6("m6", origin);

    Joint j1("j1", "t1", m1, m2, origin, origin);
    Joint j2("j2", "t2", m2, m3, origin, origin);
    Joint j3("j3", "t3", m3, m1, origin, origin);

    Joint j4("j4", "t1", m4, m5, origin, origin);
    Joint j5("j5", "t2", m5, m6, origin, origin);
    Joint j6("j6", "t3", m6, m4, origin, origin);

    g.addNode(m1);
    g.addNode(m2);

    g.addEdge(j1);
    */
}

void graphTest3()
{
    /*
    GraphType::GraphCoord<float> a(1,2);

    auto n1 = std::make_shared<GraphType::GraphNode<MotionBody, float>>(MotionBody(), a);
    auto n2 = std::make_shared<GraphType::GraphNode<MotionBody, float>>(MotionBody(), a);
    auto n3 = std::make_shared<GraphType::GraphNode<MotionBody, float>>(MotionBody(), a);
    auto n4 = std::make_shared<GraphType::GraphNode<MotionBody, float>>(MotionBody(), a);
        
    GraphType::Graph<MotionBody, float> g;

    g.addNode(n1);
    g.addNode(n2);
    g.addEdge(n1, n2);
    g.addEdge(n3, n4);
    g.addEdge(n3, n4);
    g.addEdge(n3, n4);

    

    GraphType::ForceDirectedLayout<MotionBody,float> l(g);

    l.runAlgorithm();
    */
}

void dataModelTest()
{
    auto m1 = std::make_shared<DataModel::MotionBody>("m1", DataModel::Point3D());
    auto m2 = std::make_shared<DataModel::MotionBody>("m2", DataModel::Point3D());
    auto m3 = std::make_shared<DataModel::MotionBody>("m3", DataModel::Point3D());

    std::map<std::string, std::shared_ptr<DataModel::Element>> mContainer;

    mContainer[m1->getName()] = m1;
    mContainer[m2->getName()] = m2;
    mContainer[m3->getName()] = m3;


    auto j1 = std::make_shared<DataModel::Joint>("j1",JointType::Atpoint,m1,m2, DataModel::Point3D(), DataModel::Point3D());
    auto c1 = std::make_shared<DataModel::Connector>(ConnectorKind::Damper, "c1", "type", j1);
    auto c2 = std::make_shared<DataModel::Connector>(ConnectorKind::Damper, "c2", "type2", m1,m2, DataModel::Point3D(), DataModel::Point3D());

    std::map<std::string, std::shared_ptr<DataModel::Element>> lContainer;

    lContainer[j1->getName()] = j1;
    lContainer[c1->getName()] = c1;
    lContainer[c2->getName()] = c2;

    DataModel::Mechanism mech;

    mech.addDataContainer(mContainer, DataModel::ElementType::MotionBody);

    for (auto x : mech.getContainer(DataModel::ElementType::MotionBody)) {
        

        
    }
}

int main()
{
    //graph2Test();
    //graphTest3();
    dataModelTest();
    return 0;
}