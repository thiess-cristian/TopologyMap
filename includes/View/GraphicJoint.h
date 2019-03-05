#pragma once
#include "Joint.h"
#include "Enums.h"
#include "GraphicElement.h"
#include <qgraphicsitem.h>
#include <qobject.h>

class GraphicMotionBody;

class GraphicJoint :public QObject, public GraphicElement
{
    Q_OBJECT
public:
    GraphicJoint(const Joint& joint,GraphicMotionBody* action, GraphicMotionBody* base);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
    virtual QPainterPath shape() const override;

    // Inherited via GraphicElement
    virtual void resetColor() override;

    void setActionConnection(const QPointF& action);
    void setBaseConnection(const QPointF& base);

    QPointF getActionConnection()const;
    QPointF getBaseConnection()const;

    const Joint& getModel() const;

    void connectionTranslate(QPointF translate);
    void connectionScale(double scaleFactor);

public slots:
    void changeBasePosition(const QPointF& offset);
    void changeActionPosition(const QPointF& offset);

private:
    Joint m_model;

    QPointF m_actionConnection;
    QPointF m_baseConnection;

    GraphicMotionBody* m_action;
    GraphicMotionBody* m_base;

    QRectF m_boundingRect;
};