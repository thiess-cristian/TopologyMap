#include "App\TopologyMapView.h"

using namespace App;

TopologyMapView::TopologyMapView(QWidget *parent):QGraphicsView(parent)
{
    
}

std::string TopologyMapView::getName() const
{
    return m_name;
}
