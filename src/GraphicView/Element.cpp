#include "GraphicView\Element.h"
#include "GraphicView\IElementPainter.h"
#include "GraphicView\ElementRightClickMenu.h"
#include <GraphicModel\Element.h>
#include <qgraphicssceneevent.h>
#include <qpainter.h>

#include <iostream>

using namespace GV;

Element::Element(std::shared_ptr<GM::Element> elementModel):m_elementModel(elementModel),m_rightClickMenu(elementModel)
{   
    elementModel->setGraphicViewModel(this);
}
Element:: ~Element()
{
    
}

QRectF Element::boundingRect() const
{    
    return m_elementModel->boundingRect();
}

void Element::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    m_elementPainter->paintItem(painter);
}

void Element::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
    m_rightClickMenu.processEvent(event);
}

void GV::Element::prepareViewModel()
{
    QGraphicsItem::prepareGeometryChange();
}

GV::ElementRightClickMenu & GV::Element::getRightClickMenu()
{
    return m_rightClickMenu;
}

std::shared_ptr<GM::Element> GV::Element::getModel()
{
    return m_elementModel;
}
