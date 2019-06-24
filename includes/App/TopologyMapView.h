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

    protected:
        virtual void keyPressEvent(QKeyEvent* event) override;
        virtual void keyReleaseEvent(QKeyEvent* event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
        virtual void mousePressEvent(QMouseEvent *event)override;
    
    };


}