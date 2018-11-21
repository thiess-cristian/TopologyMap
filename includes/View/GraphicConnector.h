#pragma once
#include "Connector.h"
#include "Enums.h"
#include <qgraphicsitem.h>

class GraphicConnector :public QGraphicsItem
{
public:
    GraphicConnector(Connector connector);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    void setAction(const QPoint& action);
    void setBase(const QPoint& base);

private:
    Connector m_connector;

    QPoint m_action;
    QPoint m_base;

};