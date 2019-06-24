#pragma once
#include "GraphicView\Element.h"
#include <qgraphicssceneevent.h>


namespace GV
{
    class MotionBody:public Element
    {
    public:
        MotionBody(std::shared_ptr<GM::Element> elementModel);

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        void highlightElement();
        void unHighlightElement();

    private:
        QPointF m_shiftMouseCoords;
    };


}
