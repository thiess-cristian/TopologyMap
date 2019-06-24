#include "App\TopologyMapView.h"
#include <GraphicView\MotionBody.h>

#include <qevent.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <iostream>

using namespace App;

TopologyMapView::TopologyMapView(QWidget *parent):QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
}

void TopologyMapView::keyPressEvent(QKeyEvent * event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key() == Qt::Key_Control) {
            setDragMode(QGraphicsView::RubberBandDrag);            
        }
    }
    QGraphicsView::keyPressEvent(event);
}

void TopologyMapView::keyReleaseEvent(QKeyEvent * event)
{
    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key() == Qt::Key_Control) {
            setDragMode(QGraphicsView::ScrollHandDrag);
        }
    }
    QGraphicsView::keyReleaseEvent(event);
}

void TopologyMapView::mouseReleaseEvent(QMouseEvent * event)
{        
    if (event->button() == Qt::LeftButton && event->modifiers() & Qt::CTRL) {    
        auto rect = rubberBandRect();

        auto selectedItems = items(rect);

        for (auto& item : selectedItems) {
            auto motionBody = dynamic_cast<GV::MotionBody*>(item);
            if (motionBody) {
                motionBody->highlightElement();
                motionBody->setSelected(true);
            }
        }           
    } 
    QGraphicsView::mouseReleaseEvent(event);
}

void TopologyMapView::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {           
        for (auto& item : scene()->selectedItems()) {
            
            auto motionBody = dynamic_cast<GV::MotionBody*>(item);
            if (motionBody) {
                motionBody->unHighlightElement();
                motionBody->setSelected(false);
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}
