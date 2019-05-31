#include "App\TopologyMapView.h"

using namespace App;

TopologyMapView::TopologyMapView(QWidget *parent):QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
}
