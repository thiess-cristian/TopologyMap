#include "GraphicModel\Bounder.h"

using namespace GM;

Bounder::Bounder()
{}

QRectF Bounder::createBoundingRect(const std::vector<QPointF>& points)
{
    double minX = points[0].x();
    double maxX = points[0].x();
    double minY = points[0].y();
    double maxY = points[0].y();

    for (const auto& point : points) {
        maxX = std::max(maxX, point.x());
        minX = std::min(minX, point.x());
        maxY = std::max(maxY, point.y());
        minY = std::min(minY, point.y());
    }

    return QRectF(minX, minY, maxX - minX, maxY - minY);
}