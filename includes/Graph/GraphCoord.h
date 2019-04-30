#pragma once

namespace Graph
{
    template<typename DataType>
    class GraphCoord
    {       
    public:
        GraphCoord(const DataType& x, const DataType& y);
        GraphCoord();
  
        void setX(const DataType& x);
        void setY(const DataType& y);
        DataType getX()const;
        DataType getY()const;

        double length() const;
        double lengthSquared() const;
        double distance(const GraphCoord& coord) const;

        GraphCoord operator-(const GraphCoord& coord) const;
        GraphCoord operator/(double d) const;
        GraphCoord operator*(double d) const;
        GraphCoord& operator+=(const GraphCoord& coord);
        GraphCoord& operator-=(const GraphCoord& coord);

    private:
        DataType m_x;
        DataType m_y;
    };


    template<typename DataType>
    inline GraphCoord<DataType>::GraphCoord(const DataType & x, const DataType & y) :m_x(x), m_y(y)
    {}

    template<typename DataType>
    inline GraphCoord<DataType>::GraphCoord()
    {}

    template<typename DataType>
    inline void GraphCoord<DataType>::setX(const DataType & x)
    {
        m_x = x;
    }

    template<typename DataType>
    inline void GraphCoord<DataType>::setY(const DataType & y)
    {
        m_y = y;
    }

    template<typename DataType>
    inline DataType GraphCoord<DataType>::getX() const
    {
        return m_x;
    }
    template<typename DataType>
    inline DataType GraphCoord<DataType>::getY() const
    {
        return m_y;
    }
    template<typename DataType>
    inline double GraphCoord<DataType>::length() const
    {
        return sqrt(m_x*m_x + m_y*m_y);
    }
    template<typename DataType>
    inline double GraphCoord<DataType>::lengthSquared() const
    {
        return m_x*m_x + m_y*m_y;
    }
    template<typename DataType>
    inline double GraphCoord<DataType>::distance(const GraphCoord & coord) const
    {
        return sqrt((m_x - coord.m_x)*(m_x - coord.m_x) + (m_y - coord.m_y)*(m_y - coord.m_y));
    }
    template<typename DataType>
    inline GraphCoord<DataType> GraphCoord<DataType>::operator-(const GraphCoord<DataType> & coord) const
    {
        return GraphCoord(m_x - coord.m_x, m_y - coord.m_y);
    }
    template<typename DataType>
    inline GraphCoord<DataType> GraphCoord<DataType>::operator/(double d) const
    {
        return GraphCoord(m_x / d, m_y / d);
    }
    template<typename DataType>
    inline GraphCoord<DataType> GraphCoord<DataType>::operator*(double d) const
    {
        return GraphCoord(m_x*d, m_y*d);
    }
    template<typename DataType>
    inline GraphCoord<DataType> & GraphCoord<DataType>::operator+=(const GraphCoord<DataType> & coord)
    {
        m_x += coord.m_x;
        m_y += coord.m_y;
        return *this;
    }
    template<typename DataType>
    inline GraphCoord<DataType> & GraphCoord<DataType>::operator-=(const GraphCoord<DataType> & coord)
    {
        m_x -= coord.m_x;
        m_y -= coord.m_y;
        return *this;
    }
}