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
    m_color = color;
    QGraphicsItem::update();
}

QColor GraphicElement::getColor() const
{
    return m_color;
}

void GraphicElement::enableDisplayName(bool canDisplayName)
{
    m_displayName = canDisplayName;
    QGraphicsItem::update();
}
