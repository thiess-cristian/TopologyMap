#pragma once
#include "Connector.h"
#include "Enums.h"
#include "GraphicElement.h"
#include "GraphicLink.h"
#include <qgraphicsitem.h>

class GraphicMotionBody;

class GraphicConnector :public QObject, public GraphicLink
{
    Q_OBJECT
public:
    GraphicConnector(const Connector& connector, GraphicMotionBody * action, GraphicMotionBody * base);

    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;

    // Inherited via GraphicElement
    virtual void resetColor() override;
    // Inherited via GraphicLink
    virtual std::shared_ptr<Element> getElementModel() const override;


    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    void connectionTranslate(const QPointF& translate);
    void connectionScale(double scaleFactor);

    const Connector& getModel() const;

public slots:
    void changeBasePosition(const QPointF& offset);
    void changeActionPosition(const QPointF& offset);

private:
    Connector m_model;


};