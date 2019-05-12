#pragma once
#include <memory>
#include <qgraphicsitem.h>
#include "GraphicView\ElementRightClickMenu.h"
#include "GraphicView\IElementPainter.h"

namespace GM
{
    class Element;
}

namespace GV
{
    //class ElementRightClickMenu;
    //class IElementPainter;

    class Element:public QGraphicsItem
    {
    public:
        Element(std::shared_ptr<GM::Element> elementModel);

        // Inherited via QGraphicsItem
        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;

    protected:
        std::shared_ptr<GM::Element> m_elementModel;
        std::unique_ptr<GV::ElementRightClickMenu> m_rightClickMenu;
        std::unique_ptr<GV::IElementPainter> m_elementPainter;
    };
}