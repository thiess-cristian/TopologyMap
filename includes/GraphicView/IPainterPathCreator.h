#pragma once
#include "qpainterpath.h"
#include "qpoint.h"

namespace GV
{
    class Turtle;

    class IPainterPathCreator
    {
    public:
        virtual QPainterPath getPath(QPointF begin, QPointF end) const = 0;

    protected:
        //helper functions
        void drawTriangle(Turtle& turtle, double length)const;
        void drawCircle(Turtle& turtle, double length)const;
        void drawHalfCircle(Turtle& turtle, double length) const;
        void drawRectangle(Turtle& turtle, double width, double height)const;
    };
}