#pragma once
#include "qpainterpath.h"
#include "qpoint.h"

class IPainterPathCreator
{
    virtual QPainterPath getPath(QPointF begin,QPointF end) const = 0 ;
};