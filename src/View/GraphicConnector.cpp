#include "GraphicConnector.h"
#include <qpainter.h>

GraphicConnector::GraphicConnector(Connector connector):m_connector(connector)
{}

QRectF GraphicConnector::boundingRect() const
{
    return QRectF();
}

void GraphicConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPoint begin(m_connector.getAction().getX(), m_connector.getAction().getY());
    QPoint end(m_connector.getBase().getX(), m_connector.getBase().getY());

    painter->setPen(Qt::red);
    painter->drawLine(begin, end);
}
