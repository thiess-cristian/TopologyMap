#include "GraphicJoint.h"
#include "GraphicMotionBody.h"
#include "Bounder.h"
#include "JointPainterPathCreator.h"

#include <qrect.h>
#include <qpainter.h>

GraphicJoint::GraphicJoint(const Joint & joint, GraphicMotionBody * action, GraphicMotionBody * base) :
    m_model(joint),
    m_action(action),
    m_base(base)
{
    GraphicElement::setColor(Qt::black);
    connect(action, &GraphicMotionBody::offsetChanged, this, &GraphicJoint::changeActionPosition);
    connect(base, &GraphicMotionBody::offsetChanged, this, &GraphicJoint::changeBasePosition);
}

QRectF GraphicJoint::boundingRect() const
{  
    Bounder bounder;
    return  bounder.createBoundingRect({m_actionConnection,m_baseConnection}).adjusted(-8,-8,8,8);
}

void GraphicJoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    JointPainterPathCreator creator(m_model.getType());
    auto path = creator.getPath(m_actionConnection,m_baseConnection);

    QPen pen(m_color);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPath(path);
    painter->drawEllipse(m_actionConnection, 5,5);
    painter->drawEllipse(m_baseConnection, 7, 7);

    if (m_displayName) {
        QPointF middlePoint((m_actionConnection+m_baseConnection)/2);
        painter->drawText(middlePoint + QPoint(10, 10), m_model.getName().c_str());
    }
}

QPainterPath GraphicJoint::shape() const
{
    QPointF begin(m_actionConnection.x(), m_actionConnection.y());
    QPointF end(m_baseConnection.x(), m_baseConnection.y());

    double dx = std::max(begin.x(), end.x()) - std::min(begin.x(), end.x());
    double dy = std::max(begin.y(), end.y()) - std::min(begin.y(), end.y());

    double width = 25;
    double d = sqrt(dx*dx + dy*dy);

    dx = 0.5*width*dx / d;
    dy = 0.5*width*dy / d;

    QPointF A(begin.x() - dy, begin.y() + dx);
    QPointF B(begin.x() + dy, begin.y() - dx);
    QPointF C(end.x() - dy, end.y() + dx);
    QPointF D(end.x() + dy, end.y() - dx);

    QPainterPath shape;
    shape.moveTo(A);
    shape.lineTo(B);
    shape.lineTo(C);
    shape.lineTo(D);
    shape.lineTo(A);
    
    return shape;
}

void GraphicJoint::resetColor()
{
    GraphicElement::setColor(Qt::black);
}

void GraphicJoint::setActionConnection(const QPointF& action)
{
    prepareGeometryChange();
    m_actionConnection = action;
}

void GraphicJoint::setBaseConnection(const QPointF& base)
{
    prepareGeometryChange();
    m_baseConnection = base;
}

QPointF GraphicJoint::getActionConnection() const
{
    return m_actionConnection;
}

QPointF GraphicJoint::getBaseConnection() const
{
    return m_baseConnection;
}

const Joint & GraphicJoint::getModel() const
{
    return m_model;
}

void GraphicJoint::connectionTranslate(QPointF translate)
{
    prepareGeometryChange();
    m_baseConnection += translate;
    m_actionConnection += translate;
}

void GraphicJoint::connectionScale(double scaleFactor)
{
    prepareGeometryChange();
    m_baseConnection *= scaleFactor;
    m_actionConnection *= scaleFactor;
}

void GraphicJoint::changeActionPosition(const QPointF & offset)
{
    prepareGeometryChange();
    m_actionConnection += offset;
}

void GraphicJoint::changeBasePosition(const QPointF& offset)
{
    prepareGeometryChange();
    m_baseConnection += offset;
}
