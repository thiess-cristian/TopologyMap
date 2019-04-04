#pragma once
#include <qcolor.h>
#include <qgraphicsitem.h>
#include <memory>
#include "ElementRightClickMenu.h"

class Element;

class GraphicElement:public QGraphicsItem
{
public:
    GraphicElement();

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    virtual void resetColor() = 0;
    void setColor(const QColor& color);
    QColor getColor()const;
    virtual std::shared_ptr<Element> getElementModel()const=0;

    void enableDisplayName(bool canDisplayName);

protected:
    QColor m_color;
    bool m_displayName=true;
    
};