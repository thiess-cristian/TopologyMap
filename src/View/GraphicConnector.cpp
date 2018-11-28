#include "GraphicConnector.h"
#include <qpainter.h>

GraphicConnector::GraphicConnector(Connector connector):m_connector(connector)
{
}

QRectF GraphicConnector::boundingRect() const
{
    double width = fabs(m_action.x() - m_base.x());
    double height = fabs(m_action.y() - m_base.y());

    QRectF bounding;

    double xMin = m_action.x() < m_base.x() ? m_action.x() : m_base.x();
    double xMax = m_action.x() > m_base.x() ? m_action.x() : m_base.x();
    double yMin = m_action.y() < m_base.y() ? m_action.y() : m_base.y();
    double yMax = m_action.y() > m_base.y() ? m_action.y() : m_base.y();

    bounding.setTopLeft(QPoint(xMin, yMin));
    bounding.setTopRight(QPoint(xMax, yMin));
    bounding.setBottomRight(QPoint(xMax, yMax));
    bounding.setBottomLeft(QPoint(xMin, yMax));

    return bounding;
}

void GraphicConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPoint begin(m_action.x(), m_action.y());
    QPoint end(m_base.x(), m_base.y());

    QPen pen(Qt::red);
    pen.setCosmetic(true);
    painter->setPen(pen);
    
    painter->drawLine(begin, end);
}

void GraphicConnector::setAction(const QPoint & action)
{
    m_action = action;
}

void GraphicConnector::setBase(const QPoint & base)
{
    m_base = base;
}
