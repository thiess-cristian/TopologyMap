#include "GraphicConnector.h"
#include "Bounder.h"
#include <qpainter.h>

GraphicConnector::GraphicConnector(Connector connector):m_connector(connector)
{
}

QRectF GraphicConnector::boundingRect() const
{
    Bounder bounder;
    return  bounder.createBoundingRect({m_actionConnection,m_baseConnection});
}

void GraphicConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPointF begin(m_actionConnection.x(), m_actionConnection.y());
    QPointF end(m_baseConnection.x(), m_baseConnection.y());

    QPen pen(Qt::red);
    pen.setCosmetic(true);
    painter->setPen(pen);
    
    painter->drawLine(begin, end);
}

void GraphicConnector::setActionConnection(const QPointF & action)
{
    m_actionConnection = action;
}

void GraphicConnector::setBaseConnection(const QPointF & base)
{
    m_baseConnection = base;
}

const Connector & GraphicConnector::getModel() const
{
    return m_connector;
}
