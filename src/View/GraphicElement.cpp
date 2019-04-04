#include "GraphicElement.h"
#include "ElementRightClickMenu.h"
#include <memory>

GraphicElement::GraphicElement()
{
    m_rightClickMenu= std::make_unique<ElementRightClickMenu>(*this);
}

void GraphicElement::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
    m_rightClickMenu->processEvent(event);
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

std::shared_ptr<ElementRightClickMenu> GraphicElement::getRightClickMenu() const
{
    return m_rightClickMenu;
}

void GraphicElement::enableDisplayName(bool canDisplayName)
{
    m_displayName = canDisplayName;
    QGraphicsItem::update();
}
