#pragma once
#include <qcolor.h>
#include <qgraphicsitem.h>

class GraphicElement:public QGraphicsItem
{
public:
    GraphicElement();

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    virtual void resetColor() = 0;
    void setColor(const QColor& color);
    QColor getColor()const;

    void enableDisplayName(bool canDisplayName);

protected:
    QColor m_color;
    bool m_displayName=true;
};