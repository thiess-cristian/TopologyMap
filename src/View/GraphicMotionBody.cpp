#include "GraphicMotionBody.h"
#include "qpainter.h"

GraphicMotionBody::GraphicMotionBody(MotionBody body, Perspective perspective):m_motionBody(body)
{
    switch (perspective) {
        case Perspective::TOP: {
            m_origin.setX(body.getX());
            m_origin.setY(body.getZ());
            break;
        }
        case Perspective::SIDE: {
            m_origin.setX(body.getX());
            m_origin.setY(body.getY());
            break;
        }
        case Perspective::FRONT: {
            m_origin.setX(body.getZ());
            m_origin.setY(body.getY());
            break;
        }
        default: {
            break;
        }
    }
}

QRectF GraphicMotionBody::boundingRect() const
{
    return QRectF(m_origin.x(), m_origin.y(),40,40);

}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //QGraphicsItem::paint(painter, option, widget);

    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), m_motionBody.getName().c_str());

}
