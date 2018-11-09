#pragma once
#include "Joint.h"
#include "Enums.h"
#include <qgraphicsitem.h>

class GraphicJoint :public QGraphicsItem
{
public:
    GraphicJoint(Joint joint, Perspective perspective);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

private:
    Joint m_joint;

    QPoint m_action;
    QPoint m_base;

};