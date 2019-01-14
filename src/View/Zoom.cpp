#include "Zoom.h"
#include <qgraphicsview.h>
#include <ElementsManager.h>
#include <qevent.h>
#include <qapplication.h>
#include <iostream>
#include <qgraphicsview.h>

Zoom::Zoom(QGraphicsView* view, ElementsManager* manager):m_manager(manager),m_view(view)
{
    m_view->viewport()->installEventFilter(this);
    m_view->setMouseTracking(true);
    m_zoomFactor = 1.0015;
}

void Zoom::zoom(double factor)
{
    m_manager->applyScale(factor);

    m_view->update();

   // m_view->centerOn(m_targetScenePos);
    QPointF deltaViewportPos = m_targetViewportPos - QPointF(m_view->viewport()->width() / 2.0, m_view->viewport()->height() / 2.0);
    QPointF viewportCenter = m_view->mapFromScene(m_targetScenePos) - deltaViewportPos;
   // m_view->centerOn(m_view->mapToScene(viewportCenter.toPoint()));

}

void Zoom::setZoomFactor(double value)
{
    m_zoomFactor = value;
}

bool Zoom::eventFilter(QObject * object, QEvent * event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF delta = m_targetViewportPos - mouse_event->pos();
        if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
            m_targetViewportPos = mouse_event->pos();
            m_targetScenePos = m_view->mapToScene(mouse_event->pos());
        }
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);  
        if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
            if (wheel_event->orientation() == Qt::Vertical) {
                double angle = wheel_event->angleDelta().y();
                double factor = std::pow(m_zoomFactor, angle);
                zoom(factor);
                return true;
            }
        }
    }
    return false;
}
