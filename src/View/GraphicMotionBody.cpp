#include "GraphicMotionBody.h"
#include "qpainter.h"
#include "Bounder.h"
#include <iostream>
#include <qgraphicssceneevent.h>
#include <qcursor.h>
#include <qfontmetrics.h>

GraphicMotionBody::GraphicMotionBody(MotionBody body):
    m_motionBody(body),
    m_boundingRect(QRectF())
{

}

QRectF GraphicMotionBody::boundingRect() const
{
    QRectF bounding = m_boundingRect;
    double minWidth = 50;
    double minHeight = 50;

    bounding.setWidth(std::max(bounding.width(), minWidth));
    bounding.setHeight(std::max(bounding.height(), minHeight));

    QGraphicsTextItem textItem;
    textItem.font();
    QFontMetrics metrics(textItem.font());
    int textLength = std::max(0, static_cast<int>(metrics.width(m_motionBody.getName().c_str()) - m_boundingRect.width() / 2));
    return bounding.adjusted(0, 0, textLength, 0);
}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->drawEllipse(m_origin, 10, 10);
    QRectF rect(m_boundingRect.x(), m_boundingRect.y(), m_boundingRect.width(), m_boundingRect.height());
    
    double minWidth = 50;
    double minHeight = 50;

    rect.setWidth(std::max(rect.width(), minWidth));
    rect.setHeight(std::max(rect.height(), minHeight));

    m_origin.setX(std::max(rect.center().x(), m_origin.x()));
    m_origin.setY(std::max(rect.center().y(), m_origin.y()));

    painter->fillRect(rect, QBrush(QColor(128, 128, 255, 128)));
    painter->fillRect(boundingRect(), QBrush(QColor(128, 255, 255, 128)));
    painter->drawText(m_origin, m_motionBody.getName().c_str());
}

void GraphicMotionBody::setBoundingRect(QRectF boundingRect)
{
    m_boundingRect = boundingRect;
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
    prepareGeometryChange();
    m_origin += translation;
    m_boundingRect.translate(translation);
}

void GraphicMotionBody::boundingRectScale(double scaleFactor)
{
    prepareGeometryChange();
    m_origin *= scaleFactor;
    
    m_boundingRect=QRectF(m_boundingRect.x()*scaleFactor,
                          m_boundingRect.y()*scaleFactor, 
                          m_boundingRect.width()*scaleFactor, 
                          m_boundingRect.height()*scaleFactor);
}

void GraphicMotionBody::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{    
    auto dir = event->pos() - m_shiftMouseCoords;
    boundingRectTranslate(dir);
    m_shiftMouseCoords = event->pos();

    emit offsetChanged(dir);
}

void GraphicMotionBody::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_shiftMouseCoords = event->pos();
    setCursor(QCursor(Qt::ClosedHandCursor));
}

