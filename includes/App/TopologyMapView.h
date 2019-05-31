#pragma once

#include "qgraphicsview.h"

namespace GV
{
    class TopologyMapScene;
}

namespace App
{
    class TopologyMapView:public QGraphicsView
    {
    public:
        TopologyMapView(QWidget *parent = nullptr);
    };


}