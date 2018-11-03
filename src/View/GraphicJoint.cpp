#include "GraphicJoint.h"

#include <qpainter.h>

GraphicJoint::GraphicJoint(Joint joint):m_joint(joint)
{}

QRectF GraphicJoint::boundingRect() const
{
    return QRectF();
}

void GraphicJoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPoint begin(m_joint.getAction().getX(), m_joint.getAction().getY());
    QPoint end(m_joint.getBase().getX(), m_joint.getBase().getY());

    painter->drawLine(begin, end);

}
