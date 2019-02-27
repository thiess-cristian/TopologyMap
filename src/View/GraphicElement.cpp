#include "GraphicElement.h"
#include "ElementRightClickMenu.h"
#include <memory>

GraphicElement::GraphicElement()
{

}

void GraphicElement::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
    std::unique_ptr<ElementRightClickMenu> rightClickMenu = std::make_unique<ElementRightClickMenu>(*this);
    rightClickMenu->processEvent(event);
}

void GraphicElement::setColor(const QColor & color)
{
    QGraphicsItem::update();
    m_color = color;
}
