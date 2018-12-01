#include "GraphicMotionBody.h"
#include "qpainter.h"
#include <iostream>
#include <qgraphicssceneevent.h>
#include <qcursor.h>

GraphicMotionBody::GraphicMotionBody(MotionBody body):
    m_motionBody(body),
    m_boundingRect(QRectF())
{

}

QRectF GraphicMotionBody::boundingRect() const
{
    return m_boundingRect;
}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //QGraphicsItem::paint(painter, option, widget);
    //painter->drawRect(boundingRect());
    painter->drawEllipse(m_origin, 10, 10);
    QRectF rect(m_boundingRect.x(), m_boundingRect.y(), m_boundingRect.width(), m_boundingRect.height());
    
   

    painter->fillRect(rect, QBrush(QColor(128, 128, 255, 128)));
    painter->drawText(m_origin, m_motionBody.getName().c_str());
}

void GraphicMotionBody::setBoundingRect(QRectF boundingRect)
{
    QRectF rect(boundingRect.x(), boundingRect.y(), boundingRect.width(), boundingRect.height());
    m_boundingRect = rect;

    double minWidth = 100;
    double minHeight = 100;

    m_boundingRect.setWidth(std::max(rect.width(), minWidth));
    m_boundingRect.setHeight(std::max(rect.height(), minHeight));
}

void GraphicMotionBody::setOrigin(QPointF origin)
{
    m_origin = origin;
}

const MotionBody & GraphicMotionBody::getModel() const
{
    return m_motionBody;
}

void GraphicMotionBody::boundingRectTranslate(QPointF translation)
{
    m_origin += translation;
    m_boundingRect.translate(translation);
}

void GraphicMotionBody::boundingRectScale(double scaleFactor)
{
    m_origin *= scaleFactor;
    
    m_boundingRect=QRectF(m_boundingRect.x()*scaleFactor,
                          m_boundingRect.y()*scaleFactor, 
                          m_boundingRect.width()*scaleFactor, 
                          m_boundingRect.height()*scaleFactor);
}

void GraphicMotionBody::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{    
    setPos(mapToScene(event->pos() + m_shiftMouseCoords));
    emit offsetChanged(event->pos() + m_shiftMouseCoords);
}

void GraphicMotionBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_shiftMouseCoords = pos() - mapToScene(event->pos());
    setCursor(QCursor(Qt::ClosedHandCursor));
}

