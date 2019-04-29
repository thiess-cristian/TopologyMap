#pragma once
#include "MotionBody.h"
#include "Enums.h"
#include "GraphicElement.h"
#include <qgraphicsitem.h>
#include <qrect.h>
#include <qcolor.h>

class ElementRightClickMenu;

class GraphicMotionBody :public QObject,public GraphicElement
{
    Q_OBJECT
public:
    GraphicMotionBody(MotionBody body);
    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
    
    // Inherited via GraphicElement
    virtual void resetColor() override;
    virtual std::shared_ptr<Element> getElementModel() const override;

    void setBoundingRect(const QRectF& boundingRect);
    void setOrigin(const QPointF& origin);

    const MotionBody& getModel() const;
    QPointF getOrigin()const;

    void boundingRectTranslate(QPointF translation);
    void boundingRectScale(double scaleFactor);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    bool operator==(const GraphicMotionBody& other) const;
signals:
    void offsetChanged(const QPointF& offset);

private:
    QPointF m_shiftMouseCoords;
    MotionBody m_model;
    QPointF m_origin;
    QRectF m_boundingRect;    
};