#pragma once
#include "Joint.h"
#include "Enums.h"
#include <qgraphicsitem.h>

class GraphicMotionBody;

class GraphicJoint :public QGraphicsItem
{
public:
    GraphicJoint(const Joint& joint,GraphicMotionBody* action, GraphicMotionBody* base);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    void setActionConnection(const QPointF& action);
    void setBaseConnection(const QPointF& base);

    const Joint& getModel() const;

private:
    Joint m_joint;

    QPointF m_actionConnection;
    QPointF m_baseConnection;

    GraphicMotionBody* m_action;
    GraphicMotionBody* m_base;


};