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

    painter->fillRect(boundingRect(), QBrush(QColor(128, 128, 255, 128)));
    painter->drawText(boundingRect(), m_motionBody.getName().c_str());

}

void GraphicMotionBody::setBoundingRect(QRectF boundingRect)
{
    m_boundingRect = boundingRect;
}

void GraphicMotionBody::setOrigin(QPoint origin)
{
    m_origin = origin;
}

