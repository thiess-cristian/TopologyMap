#include "GraphicJoint.h"
#include "GraphicMotionBody.h"
#include "Bounder.h"
#include "JointPainterPathCreator.h"

#include <qrect.h>
#include <qpainter.h>

GraphicJoint::GraphicJoint(const Joint & joint, GraphicMotionBody * action, GraphicMotionBody * base) :
    m_joint(joint),
    m_action(action),
    m_base(base)
{
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
    QPen pen(Qt::black);
    pen.setCosmetic(true);
    painter->setPen(pen);

    //painter->drawLine(m_actionConnection, m_baseConnection);

    JointPainterPathCreator creator(m_joint.getType());

    auto path = creator.getPath(m_actionConnection,m_baseConnection);

    painter->drawPath(path);
    painter->drawEllipse(m_actionConnection, 5,5);
    painter->drawEllipse(m_baseConnection, 7, 7);
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

const Joint & GraphicJoint::getModel() const
{
    return m_joint;
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
