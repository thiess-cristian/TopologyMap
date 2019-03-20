#include "GraphicLink.h"
#include "GraphicMotionBody.h"

GraphicLink::GraphicLink(GraphicMotionBody * action, GraphicMotionBody * base):GraphicElement(),m_action(action),m_base(base)
{
    m_overlappingCount = 0;
}

void GraphicLink::setOverlappingCount(size_t i)
{
    m_overlappingCount = i;
}

size_t GraphicLink::getOverlappingCount()
{
    return m_overlappingCount;
}

void GraphicLink::setReverseOverlaps(bool reverseOverlaps)
{
    m_reverseOverlap = true;
}

bool GraphicLink::isReverseOverlap()
{
    return m_reverseOverlap;
}

void GraphicLink::setActionConnection(const QPointF & action)
{
    prepareGeometryChange();
    m_actionConnection = action;
}

void GraphicLink::setBaseConnection(const QPointF & base)
{
    prepareGeometryChange();
    m_baseConnection = base;
}

QPointF GraphicLink::getActionConnection() const
{
    return m_actionConnection;
}

QPointF GraphicLink::getBaseConnection() const
{
    return m_baseConnection;
}

bool GraphicLink::overlaps(const GraphicLink & other)
{
    return *m_action == *other.m_action && *m_base == *other.m_base;
}

bool GraphicLink::reverseOverlaps(const GraphicLink & other)
{
    return *m_action == *other.m_base && *m_base == *other.m_action;
}
