#include "GraphicJoint.h"
#include "GraphicMotionBody.h"
#include "Bounder.h"

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
    return  bounder.createBoundingRect({m_actionConnection,m_baseConnection});
}

void GraphicJoint::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->drawLine(m_actionConnection, m_baseConnection);

    painter->drawEllipse(m_actionConnection, 5,5);
    painter->drawEllipse(m_baseConnection, 7, 7);
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

void GraphicJoint::changeActionPosition(const QPointF & offset)
{
    m_actionConnection += offset;
}

void GraphicJoint::changeBasePosition(const QPointF& offset)
{
    m_baseConnection += offset;
}
