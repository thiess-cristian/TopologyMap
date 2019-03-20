#pragma once
#include "Joint.h"
#include "Enums.h"
#include "GraphicElement.h"
#include "GraphicLink.h"
#include <qgraphicsitem.h>
#include <qobject.h>

class GraphicMotionBody;

class GraphicJoint :public QObject, public GraphicLink
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

    const Joint& getModel() const;

    void connectionTranslate(QPointF translate);
    void connectionScale(double scaleFactor);

public slots:
    void changeBasePosition(const QPointF& offset);
    void changeActionPosition(const QPointF& offset);

private:
    Joint m_model;
    QRectF m_boundingRect;
};