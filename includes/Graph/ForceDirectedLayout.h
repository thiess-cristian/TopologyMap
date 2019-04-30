#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <Graph\Graph.h>
#include <set>
#include <chrono>

namespace Graph
{
    template<typename T,typename D>
    class ForceDirectedLayout
    {
    public:
        ForceDirectedLayout(const Graph<T, D>& graph):m_graph(graph)
        {

        }
        void runAlgorithm();
        void setConvergenceFactor(double value);
        
    private:
        void makeCircle();
        void resetDisplacement();
        void calculateRepulsiveForces();
        void calculateAttractiveForces();
        void setNewPosition();
        
        Graph<T, D> m_graph;

        size_t m_size = 0;
        const double m_k = 0.01;
        double m_e = 0.001;
        bool m_convergent = false;
    };


    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::runAlgorithm()
    {
        for (auto &node : m_graph.nodes()) {
            std::set<std::shared_ptr<GraphNode<T, D>>> s(node->getNeighbourNodes().begin(), node->getNeighbourNodes().end());
            node->getNeighbourNodes().assign(s.begin(), s.end());
        }

        m_size = m_graph.nodes().size();

        makeCircle();

        auto start = std::chrono::steady_clock::now();
        while (!m_convergent) {
            resetDisplacement();
            calculateRepulsiveForces();
            calculateAttractiveForces();
            setNewPosition();
        }
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
        std::cout << std::endl;
        std::cout << duration.count();
        
    }

    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::setConvergenceFactor(double value)
    {
        m_e = value;
    }

    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::makeCircle()
    {
        int i = 0;
        std::for_each(m_graph.nodes().begin(), m_graph.nodes().end(), [&](std::shared_ptr<GraphNode<T, D>> n) {
            D x = cos((2 * M_PI*i) / m_size);
            D y = sin((2 * M_PI*i) / m_size);
            i++;
            n->setPosition(x, y);
        });
        
    }

    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::resetDisplacement()
    {
        std::for_each(m_graph.nodes().begin(), m_graph.nodes().end(), [](std::shared_ptr<GraphNode<T, D>> n) { 
            n->setDisplacement(0, 0); 
        });
    }

    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::calculateRepulsiveForces()
    {
        for (size_t i = 0; i < m_size - 1; i++) {

            auto &nodeV = m_graph.nodes()[i];
            auto &nodeVPos = nodeV->getPosition();

            for (size_t j = i + 1; j < m_size; j++) {

                auto &nodeU = m_graph.nodes()[j];
                auto &nodeUPos = nodeU->getPosition();

                auto displacement = (nodeVPos - nodeUPos);
                displacement = displacement * m_k / displacement.lengthSquared();
                nodeV->getDisplacement() += displacement;
                nodeU->getDisplacement() -= displacement;
            }
        }   
    }

    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::calculateAttractiveForces()
    {
        for (size_t i = 0; i < m_size; i++) {
            auto &nodeV = m_graph.nodes()[i];
            auto &nodeVPos = nodeV->getPosition();

            for (size_t j = 0; j < nodeV->getNeighbourNodes().size(); j++) {
                auto &nodeU = nodeV->getNeighbourNodes()[j];
                auto &nodeUPos = nodeU->getPosition();

                auto displacement = (nodeVPos - nodeUPos) * m_k;
                nodeV->getDisplacement() -= displacement;
                nodeU->getDisplacement() += displacement;
            }
        }
    }

    template<typename T, typename D>
    inline void ForceDirectedLayout<T, D>::setNewPosition()
    {
        double maxDistance = -DBL_MIN;

        for (size_t i = 0; i < m_size; i++) {
            auto& node = m_graph.nodes()[i];

            if (node->getNeighbourNodes().size() != 0) {
                auto curentPos = node->getPosition();
                node->getPosition() += node->getDisplacement();

                if (curentPos.distance(node->getPosition()) > maxDistance) {
                    maxDistance = curentPos.distance(node->getPosition());
                }
            }
        }

        if(maxDistance < m_e) {
            m_convergent = true;
        }    
    }
}