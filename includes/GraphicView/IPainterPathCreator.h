#pragma once
#include "qpainterpath.h"
#include "qpoint.h"
namespace GV
{
    class IPainterPathCreator
    {
        virtual QPainterPath getPath(QPointF begin, QPointF end) const = 0;
    };
}