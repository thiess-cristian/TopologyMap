#include "GraphicMotionBody.h"
#include "qpainter.h"

GraphicMotionBody::GraphicMotionBody(MotionBody body):
    m_motionBody(body),
    m_boundingRect(QRectF())
{

}

QRectF GraphicMotionBody::boundingRect() const
{
    return m_boundingRect;
}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //QGraphicsItem::paint(painter, option, widget);
    //painter->drawRect(boundingRect());
    painter->drawEllipse(m_origin, 10, 10);
    QRectF rect(m_boundingRect.x() + 10, m_boundingRect.y() + 10, m_boundingRect.width() - 10, m_boundingRect.height() -10);
    
    painter->fillRect(rect, QBrush(QColor(128, 128, 255, 128)));
    painter->drawText(m_origin, m_motionBody.getName().c_str());
}

void GraphicMotionBody::setBoundingRect(QRectF boundingRect)
{
    QRectF rect(boundingRect.x() - 10, boundingRect.y() - 10, boundingRect.width() + 10, boundingRect.height() + 10);
    m_boundingRect = rect;

    double minWidth = 100;
    double minHeight = 100;

    m_boundingRect.setWidth(std::max(rect.width(), minWidth));
    m_boundingRect.setHeight(std::max(rect.height(), minHeight));
}

void GraphicMotionBody::setOrigin(QPointF origin)
{
    m_origin = origin;
}

const MotionBody & GraphicMotionBody::getModel() const
{
    return m_motionBody;
}

