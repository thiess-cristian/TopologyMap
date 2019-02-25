#include "GraphicMotionBody.h"
#include "qpainter.h"
#include "Bounder.h"
#include <iostream>
#include <qgraphicssceneevent.h>
#include <qcursor.h>
#include <qfontmetrics.h>
#include <qmenu.h>
#include <qaction.h>

GraphicMotionBody::GraphicMotionBody(MotionBody body):
    m_model(body),
    m_boundingRect(QRectF())
{
    GraphicElement::setColor(QColor(128, 128, 255, 128));
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
    int textLength = std::max(0, static_cast<int>(metrics.width(m_model.getName().c_str()) - m_boundingRect.width() / 2));
    return bounding.adjusted(0, 0, textLength, 0);
}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

    QPen pen(Qt::black);
    pen.setCosmetic(true);
    painter->setPen(pen);

    //painter->drawEllipse(m_origin, 10, 10);
    QRectF rect(m_boundingRect.x(), m_boundingRect.y(), m_boundingRect.width(), m_boundingRect.height());
    
    double minWidth = 50;
    double minHeight = 50;

    rect.setWidth(std::max(rect.width(), minWidth));
    rect.setHeight(std::max(rect.height(), minHeight));

    //m_origin.setX(std::max(rect.center().x(), m_origin.x()));
    //m_origin.setY(std::max(rect.center().y(), m_origin.y()));

    painter->fillRect(rect, QBrush(m_color));
   // painter->fillRect(rect, QBrush(QColor(128, 128, 255)));
    painter->drawText(m_origin+QPoint(10,10), m_model.getName().c_str());
}

void GraphicMotionBody::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
    QMenu menu;
    QAction *removeAction = menu.addAction("Remove");
    QAction *changeColor = menu.addAction("Change color");
    QAction *selectedAction = menu.exec(event->screenPos());
}

void GraphicMotionBody::setBoundingRect(const QRectF& boundingRect)
{
    m_boundingRect = boundingRect;
}

void GraphicMotionBody::setOrigin(const QPointF& origin)
{
    m_origin = origin;
}

const MotionBody & GraphicMotionBody::getModel() const
{
    return m_model;
}

QPointF GraphicMotionBody::getOrigin() const
{
    return m_origin;
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

