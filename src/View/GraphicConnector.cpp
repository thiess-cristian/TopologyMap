#include "GraphicConnector.h"
#include "Bounder.h"
#include "GraphicMotionBody.h"
#include "ConnectorPainterPathCreator.h"
#include <qpainter.h>
#include <qtransform>
#include <iostream>

GraphicConnector::GraphicConnector(const Connector& connector, GraphicMotionBody * action, GraphicMotionBody * base):
    m_model(connector),
    m_action(action),
    m_base(base)
{
    GraphicElement::setColor(Qt::red);
    connect(action, &GraphicMotionBody::offsetChanged, this, &GraphicConnector::changeActionPosition);
    connect(base, &GraphicMotionBody::offsetChanged, this, &GraphicConnector::changeBasePosition);
}

QRectF GraphicConnector::boundingRect() const
{
    Bounder bounder;
    return  bounder.createBoundingRect({m_actionConnection,m_baseConnection});
}

QPainterPath GraphicConnector::shape() const
{
    QPainterPath shape;

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

    shape.moveTo(A);
    shape.lineTo(B);
    shape.lineTo(C);
    shape.lineTo(D);
    shape.lineTo(A);

    return shape;
}

void GraphicConnector::resetColor()
{
    GraphicElement::setColor(Qt::red);
}

void GraphicConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPointF begin(m_actionConnection.x(), m_actionConnection.y());
    QPointF end(m_baseConnection.x(), m_baseConnection.y());

    QLineF line(begin, end);

    ConnectorPainterPathCreator creator(m_model.getKind());

    auto path=creator.getPath(begin, end);

    QPen pen(m_color);
    pen.setCosmetic(true);
    painter->setPen(pen);
    //painter->drawLine(begin, end);
    painter->drawPath(path);

    QPointF middlePoint((m_actionConnection + m_baseConnection) / 2);
    painter->drawText(middlePoint + QPoint(10, 10), m_model.getName().c_str());
}

void GraphicConnector::setActionConnection(const QPointF & action)
{
    prepareGeometryChange();
    m_actionConnection = action;
}

void GraphicConnector::setBaseConnection(const QPointF & base)
{
    prepareGeometryChange();
    m_baseConnection = base;
}

QPointF GraphicConnector::getActionConnection() const
{
    return m_actionConnection;
}

QPointF GraphicConnector::getBaseConnection() const
{
    return m_baseConnection;
}

void GraphicConnector::connectionTranslate(const QPointF& translate)
{
    prepareGeometryChange();
    m_baseConnection += translate;
    m_actionConnection += translate;
}

void GraphicConnector::connectionScale(double scaleFactor)
{
    prepareGeometryChange();
    m_baseConnection*=scaleFactor;
    m_actionConnection *= scaleFactor;
}

const Connector & GraphicConnector::getModel() const
{
    return m_model;
}

void GraphicConnector::changeActionPosition(const QPointF & offset)
{
    prepareGeometryChange();
    m_actionConnection += offset;
}

void GraphicConnector::changeBasePosition(const QPointF& offset)
{
    prepareGeometryChange();
    m_baseConnection += offset;
}
