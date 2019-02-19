#include "GraphicConnector.h"
#include "Bounder.h"
#include "GraphicMotionBody.h"
#include "ConnectorPainterPathCreator.h"
#include <qpainter.h>
#include <qtransform>
#include <iostream>

GraphicConnector::GraphicConnector(const Connector& connector, GraphicMotionBody * action, GraphicMotionBody * base):
    m_connector(connector),
    m_action(action),
    m_base(base)
{
    connect(action, &GraphicMotionBody::offsetChanged, this, &GraphicConnector::changeActionPosition);
    connect(base, &GraphicMotionBody::offsetChanged, this, &GraphicConnector::changeBasePosition);
}

QRectF GraphicConnector::boundingRect() const
{
    Bounder bounder;
    return  bounder.createBoundingRect({m_actionConnection,m_baseConnection});
}

void GraphicConnector::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPointF begin(m_actionConnection.x(), m_actionConnection.y());
    QPointF end(m_baseConnection.x(), m_baseConnection.y());

    QLineF line(begin, end);

    ConnectorPainterPathCreator creator(m_connector.getKind());

    auto path=creator.getPath(begin, end);

    QPen pen(Qt::red);
    pen.setCosmetic(true);
    painter->setPen(pen);
   // painter->drawLine(begin, end);
    painter->drawPath(path);
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
    return m_connector;
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
