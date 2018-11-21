#pragma once
#include "Joint.h"
#include "Enums.h"
#include <qgraphicsitem.h>

class GraphicJoint :public QGraphicsItem
{
public:
    GraphicJoint(Joint joint);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    void setAction(const QPoint& action);
    void setBase(const QPoint& base);

private:
    Joint m_joint;

    QPoint m_action;
    QPoint m_base;

};