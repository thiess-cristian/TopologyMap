#pragma once
#include "MotionBody.h"
#include "Enums.h"
#include <qgraphicsitem.h>
#include <qrect.h>

class GraphicMotionBody :public QGraphicsItem
{
public:
    GraphicMotionBody(MotionBody body);
    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    void setBoundingRect(QRectF boundingRect);
    void setOrigin(QPoint origin);

private:
    MotionBody m_motionBody;
    QPoint m_origin;
    QRectF m_boundingRect;
};