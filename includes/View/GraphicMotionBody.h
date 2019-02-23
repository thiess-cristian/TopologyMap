#pragma once
#include "MotionBody.h"
#include "Enums.h"
#include "GraphicElement.h"
#include <qgraphicsitem.h>
#include <qrect.h>
#include <qcolor.h>

class GraphicMotionBody :public QObject,public QGraphicsItem,public GraphicElement
{
    Q_OBJECT
public:
    GraphicMotionBody(MotionBody body);
    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setBoundingRect(const QRectF& boundingRect);
    void setOrigin(const QPointF& origin);

    const MotionBody& getModel() const;
    QPointF getOrigin()const;

    void boundingRectTranslate(QPointF translation);
    void boundingRectScale(double scaleFactor);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void offsetChanged(const QPointF& offset);
private:
    QPointF m_shiftMouseCoords;
    MotionBody m_model;
    QPointF m_origin;
    QRectF m_boundingRect;
};