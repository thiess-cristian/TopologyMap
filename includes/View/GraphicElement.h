#pragma once
#include <qcolor.h>
#include <qgraphicsitem.h>
#include <memory>

class Element;
class ElementRightClickMenu;

class GraphicElement:public QGraphicsItem
{
public:
    GraphicElement();

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    virtual void resetColor() = 0;
    void setColor(const QColor& color);
    QColor getColor()const;
    virtual std::shared_ptr<Element> getElementModel()const=0;
    std::shared_ptr<ElementRightClickMenu> getRightClickMenu() const;


    void enableDisplayName(bool canDisplayName);

protected:
    QColor m_color;
    bool m_displayName=true;
    std::shared_ptr<ElementRightClickMenu> m_rightClickMenu;
};