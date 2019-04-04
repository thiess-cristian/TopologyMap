#include "GraphicConnector.h"
#include "Bounder.h"
#include "GraphicMotionBody.h"
#include "ConnectorPainterPathCreator.h"
#include "GraphicLink.h"
#include <qpainter.h>
#include <qtransform>
#include <iostream>

GraphicConnector::GraphicConnector(const Connector& connector, GraphicMotionBody * action, GraphicMotionBody * base):
    GraphicLink(action,base),
    m_model(connector)
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

    QPointF dir = end - begin;
    QPointF perpendicular(-1 * dir.y(), dir.x());

    double length = sqrt(pow(perpendicular.x(), 2) + pow(perpendicular.y(), 2));

    if (length != 0) {

        perpendicular /= length;

        int xPositionOffset = m_overlappingCount - m_overlappingCount % 2;
        xPositionOffset *= m_overlappingCount % 2 ? 1 : -1;
        int yPositionOffset = m_overlappingCount;

        if (m_reverseOverlap) {
            xPositionOffset *= -1;
        }

        begin += perpendicular*xPositionOffset * 10;
        begin += dir*yPositionOffset*0.05;
        end += perpendicular*xPositionOffset * 10;
        end -= dir*yPositionOffset*0.05;
    }

    ConnectorPainterPathCreator creator(m_model.getKind());

    QPainterPath path;
    path.moveTo(m_actionConnection);
    path.lineTo(begin);
    path.addPath(creator.getPath(begin, end));
    path.lineTo(m_baseConnection);
    
    QPen pen(m_color);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPath(path);
    if (m_displayName) {
        QPointF middlePoint((begin + end) / 2);
        painter->drawText(middlePoint + QPoint(10, 10), m_model.getName().c_str());
    }
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

std::shared_ptr<Element> GraphicConnector::getElementModel() const
{
    return std::shared_ptr<Element>();
}

void GraphicConnector::changeBasePosition(const QPointF& offset)
{
    prepareGeometryChange();
    m_baseConnection += offset;
}
