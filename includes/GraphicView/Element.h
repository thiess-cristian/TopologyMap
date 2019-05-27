#pragma once
#include <memory>
#include <qgraphicsitem.h>
#include "GraphicView\ElementRightClickMenu.h"
#include "GraphicView\IElementPainter.h"

class QGraphicsSceneContextMenuEvent;

namespace GM
{
    class Element;
}

namespace GV
{
    class Element:public QGraphicsItem
    {
    public:
        Element(std::shared_ptr<GM::Element> elementModel);
        ~Element();

        // Inherited via QGraphicsItem
        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr) override;
        virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

        void prepareViewModel();

        GV::ElementRightClickMenu& getRightClickMenu();
        std::shared_ptr<GM::Element> getModel();

    protected:
        std::shared_ptr<GM::Element> m_elementModel;
        GV::ElementRightClickMenu m_rightClickMenu;
        std::unique_ptr<GV::IElementPainter> m_elementPainter;
    };
}