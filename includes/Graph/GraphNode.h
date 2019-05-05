#pragma once
#include <Graph\GraphCoord.h>
#include <vector>
#include <memory>
#include <algorithm>

namespace Graph
{
    template<typename DataObject, typename DataType>
    class GraphNode
    {
    public:
        GraphNode(const DataObject& data, const GraphCoord<DataType>& position);

        bool isNeighbour(const GraphNode& node) const;
        void addNeighbour(std::shared_ptr<GraphNode> node);

        auto& getNeighbourNodes();
        void setPosition(const DataType& x, const DataType& y);
        void setDisplacement(const DataType& x, const DataType& y);
        auto& getDisplacement();
        auto& getPosition();
        auto getData()const;

    private:
        DataObject m_data;
        std::vector<std::shared_ptr<GraphNode>> m_neighbourNodes;

        GraphCoord<DataType> m_displacement;
        GraphCoord<DataType> m_position;
    };

    ///////////////////////////////////////////////////////////////////////////////////////
    //implementations
    template<typename DataObject, typename DataType>
    inline GraphNode<DataObject, DataType>::GraphNode(const DataObject & data, const GraphCoord<DataType>& position) :m_data(data), m_position(position), m_displacement()
    {}

    template<typename DataObject, typename DataType>
    inline bool GraphNode<DataObject, DataType>::isNeighbour(const GraphNode & node) const
    {
        return std::any_of(m_neighbourNodes.begin(), m_neighbourNodes.end(), [&node](std::shared_ptr<GraphNode> n) {
            return node.m_data == n->m_data;
        });
    }

    template<typename DataObject, typename DataType>
    inline void GraphNode<DataObject, DataType>::addNeighbour(std::shared_ptr<GraphNode> node)
    {
        m_neighbourNodes.push_back(node);
    }

    template<typename DataObject, typename DataType>
    inline auto& GraphNode<DataObject, DataType>::getNeighbourNodes()
    {
        return m_neighbourNodes;
    }

    template<typename DataObject, typename DataType>
    inline void GraphNode<DataObject, DataType>::setPosition(const DataType & x, const DataType & y)
    {
        m_position.setX(x);
        m_position.setY(y);
    }

    template<typename DataObject, typename DataType>
    inline void GraphNode<DataObject, DataType>::setDisplacement(const DataType & x, const DataType & y)
    {
        m_displacement.setX(x);
        m_displacement.setY(y);
    }

    template<typename DataObject, typename DataType>
    inline auto& GraphNode<DataObject, DataType>::getDisplacement()
    {
        return m_displacement;
    }

    template<typename DataObject, typename DataType>
    inline auto& GraphNode<DataObject, DataType>::getPosition()
    {
        return m_position;
    }

    template<typename DataObject, typename DataType>
    inline auto GraphNode<DataObject, DataType>::getData() const
    {
        return m_data;
    }
}