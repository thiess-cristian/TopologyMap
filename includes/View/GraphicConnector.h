#pragma once
#include "Connector.h"
#include <qgraphicsitem.h>

class GraphicConnector :public QGraphicsItem
{
public:
    GraphicConnector(Connector connector);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

private:
    Connector m_connector;

};