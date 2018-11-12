#include "GraphicConnector.h"
#include <qpainter.h>

GraphicConnector::GraphicConnector(Connector connector, Perspective perspective):m_connector(connector)
{
    auto action=m_connector.getAction();
    auto base = m_connector.getBase();

    switch (perspective) {
        case Perspective::SIDE: {
            m_action.setX(action.getX());
            m_action.setY(action.getZ());

            m_base.setX(base.getX());
            m_base.setY(base.getZ());
            break;
        }
        case Perspective::TOP: {
            m_action.setX(action.getX());
            m_action.setY(action.getY());

            m_base.setX(base.getX());
            m_base.setY(base.getY());
            break;
        }
        case Perspective::FRONT: {
            m_action.setX(action.getZ());
            m_action.setY(action.getY());

            m_base.setX(base.getZ());
            m_base.setY(base.getY());
            break;
        }
        default: {
            break;
        }
    }
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

    painter->setPen(Qt::red);
    painter->drawLine(begin, end);
}
