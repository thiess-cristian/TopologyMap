#pragma once
#include "MotionBody.h"
#include "Enums.h"
#include <qgraphicsitem.h>


class GraphicMotionBody :public QGraphicsItem
{
public:
    GraphicMotionBody(MotionBody body,Perspective perspective);
    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

private:
    MotionBody m_motionBody;
    QPoint m_origin;
};