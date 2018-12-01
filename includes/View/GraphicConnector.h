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

    void setActionConnection(const QPointF& action);
    void setBaseConnection(const QPointF& base);

    void connectionTranslate(QPointF translate);
    void connectionScale(double scaleFactor);

    const Connector& getModel() const;

private:
    Connector m_connector;

    QPointF m_actionConnection;
    QPointF m_baseConnection;

};