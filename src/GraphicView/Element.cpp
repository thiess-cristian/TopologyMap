#include "GraphicView\Element.h"
#include "GraphicView\IElementPainter.h"
#include "GraphicView\ElementRightClickMenu.h"
#include <GraphicModel\Element.h>
#include <qpainter.h>

using namespace GV;

Element::Element(std::shared_ptr<GM::Element> elementModel):m_elementModel(elementModel)
{
    m_rightClickMenu = std::make_unique<ElementRightClickMenu>(m_elementModel);
}

QRectF Element::boundingRect() const
{
    return m_elementModel->boundingRect();
}

void Element::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    m_elementPainter->paintItem(painter);
}