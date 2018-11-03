#include "GraphicMotionBody.h"
#include "qpainter.h"

GraphicMotionBody::GraphicMotionBody(MotionBody body):m_motionBody(body)
{}

QRectF GraphicMotionBody::boundingRect() const
{
    return QRectF(m_motionBody.getX(),m_motionBody.getY(),20,20);
}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //QGraphicsItem::paint(painter, option, widget);

    painter->drawRect(boundingRect());

}
