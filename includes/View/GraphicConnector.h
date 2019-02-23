#pragma once
#include "Connector.h"
#include "Enums.h"
#include "GraphicElement.h"
#include <qgraphicsitem.h>

class GraphicMotionBody;

class GraphicConnector :public QObject,public QGraphicsItem, public GraphicElement
{
    Q_OBJECT
public:
    GraphicConnector(const Connector& connector, GraphicMotionBody * action, GraphicMotionBody * base);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    void setActionConnection(const QPointF& action);
    void setBaseConnection(const QPointF& base);

    QPointF getActionConnection()const;
    QPointF getBaseConnection()const;

    void connectionTranslate(const QPointF& translate);
    void connectionScale(double scaleFactor);

    const Connector& getModel() const;

public slots:
    void changeBasePosition(const QPointF& offset);
    void changeActionPosition(const QPointF& offset);

private:
    Connector m_connector;

    QPointF m_actionConnection;
    QPointF m_baseConnection;

    GraphicMotionBody* m_action;
    GraphicMotionBody* m_base;
};