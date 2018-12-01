#include "GraphicJoint.h"

#include <qpainter.h>

GraphicJoint::GraphicJoint(const Joint & joint, GraphicMotionBody * action, GraphicMotionBody * base) :
    m_joint(joint),
    m_action(action),
    m_base(base)
{

}

QRectF GraphicJoint::boundingRect() const
{  
    double width = fabs(m_actionConnection.x() - m_baseConnection.x());
    double height = fabs(m_actionConnection.y() - m_baseConnection.y());

    QRectF bounding;
    //TODO: change
    double xMin = m_actionConnection.x() < m_baseConnection.x() ? m_actionConnection.x() : m_baseConnection.x();
    double xMax = m_actionConnection.x() > m_baseConnection.x() ? m_actionConnection.x() : m_baseConnection.x();
    double yMin = m_actionConnection.y() < m_baseConnection.y() ? m_actionConnection.y() : m_baseConnection.y();
    double yMax = m_actionConnection.y() > m_baseConnection.y() ? m_actionConnection.y() : m_baseConnection.y();

    bounding.setTopLeft(QPoint(xMin,yMin));
    bounding.setTopRight(QPoint(xMax,yMin));
    bounding.setBottomRight(QPoint(xMax,yMax));
    bounding.setBottomLeft(QPoint(xMin,yMax));


 
    return bounding;
}

void GraphicJoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPointF begin(m_actionConnection.x(), m_actionConnection.y());
    QPointF end(m_baseConnection.x(), m_baseConnection.y());

    painter->drawLine(begin, end);

    painter->drawEllipse(begin, 5,5);
    painter->drawEllipse(end, 7, 7);
}

void GraphicJoint::setActionConnection(const QPointF& action)
{
    m_actionConnection = action;
}

void GraphicJoint::setBaseConnection(const QPointF& base)
{
    m_baseConnection = base;
}

const Joint & GraphicJoint::getModel() const
{
    return m_joint;
}

void GraphicJoint::connectionTranslate(QPointF translate)
{
    m_baseConnection += translate;
    m_actionConnection += translate;
}

void GraphicJoint::connectionScale(double scaleFactor)
{
    m_baseConnection *= scaleFactor;
    m_actionConnection *= scaleFactor;
}
