#pragma once

#include <qpoint.h>
#include <qrect.h>
#include <vector>

namespace GM
{
    class Bounder
    {
    public:
        Bounder();
        QRectF createBoundingRect(const std::vector<QPointF>& points);
    };

}