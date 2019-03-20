#pragma once
#include "GraphicElement.h"
#include "GraphicMotionBody.h"
#include <qpoint.h>



class GraphicLink : public GraphicElement
{
public:
    GraphicLink(GraphicMotionBody * action, GraphicMotionBody * base);

    void setOverlappingCount(size_t i);
    size_t getOverlappingCount();

    void setReverseOverlaps(bool reverseOverlaps);
    bool isReverseOverlap();

    void setActionConnection(const QPointF& action);
    void setBaseConnection(const QPointF& base);

    QPointF getActionConnection()const;
    QPointF getBaseConnection()const;

    bool overlaps(const GraphicLink& other);
    bool reverseOverlaps(const GraphicLink& other);

protected:
    QPointF m_actionConnection;
    QPointF m_baseConnection;

    size_t m_overlappingCount = 0;
    bool m_reverseOverlap = false;

    GraphicMotionBody* m_action;
    GraphicMotionBody* m_base;

};