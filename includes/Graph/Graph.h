#pragma once
#include "GraphNode.h"
#include <memory>
#include <exception>

namespace Graph
{
    template<typename T,typename D>
    class Graph
    {
    public:
        void addNode(std::shared_ptr<GraphNode<T, D>> node);
        void addEdge(std::shared_ptr<GraphNode<T, D>> firstNode, std::shared_ptr<GraphNode<T, D>> secondNode);
        size_t size()const;

        auto& nodes();
        auto getNodes() const;

    private:
        std::vector<std::shared_ptr<GraphNode<T,D>>> m_nodes;
    };


    template<typename T, typename D>
    inline void Graph<T, D>::addNode(std::shared_ptr<GraphNode<T, D>> node)
    {
        m_nodes.push_back(node);
    }

    template<typename T, typename D>
    inline void Graph<T, D>::addEdge(std::shared_ptr<GraphNode<T, D>> firstNode, std::shared_ptr<GraphNode<T, D>> secondNode)
    {
        if (std::find(m_nodes.begin(), m_nodes.end(), firstNode) == m_nodes.end()) {
            addNode(firstNode);
        }

        if (std::find(m_nodes.begin(), m_nodes.end(), secondNode) == m_nodes.end()) {
            addNode(secondNode);
        }
        firstNode->addNeighbour(secondNode);
        secondNode->addNeighbour(firstNode);
    }

    template<typename T, typename D>
    inline size_t Graph<T, D>::size() const
    {
        return m_nodes.size();
    }

    template<typename T, typename D>
    inline auto& Graph<T, D>::nodes()
    {
        return m_nodes;
    }

    template<typename T, typename D>
    inline auto Graph<T, D>::getNodes() const
    {
        return m_nodes;
    }

}