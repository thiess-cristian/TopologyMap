#include "App\SceneZoom.h"
#include <qgraphicsview.h>
#include <qgraphicsscene.h>
#include <qevent.h>
#include <qapplication.h>
#include <GraphicModel\Mechanism.h>
#include <GraphicModel\Element.h>
#include <GraphicModel\MotionBody.h>
#include <qgraphicsitem.h>

using namespace App;

SceneZoom::SceneZoom(QGraphicsView* view):m_view(view)
{      
    m_view->viewport()->installEventFilter(this);
    m_view->setMouseTracking(true);
    m_zoomFactor = 1.0015;
}

void App::SceneZoom::setMechanism(std::shared_ptr<GM::Mechanism> mechanism)
{
    m_mechanism = mechanism;
}

void App::SceneZoom::zoom(double factor)
{
    if (m_mechanism) {
        for (auto container : m_mechanism->getElements()) {
            for (auto element : container.second) {
                element.second->scaleOrigin(factor);
            }
        }

        double scaleChange = factor - m_oldZoomFactor;
        double offSetY = -(m_targetViewportPos.y()*scaleChange);
        double offSetX = -(m_targetViewportPos.x()*scaleChange);
        QPointF offset(offSetX, offSetY);

        for (auto container : m_mechanism->getElements()) {
            for (auto element : container.second) {
                element.second->translate(offset);
            }

        }               
        m_view->setSceneRect(m_view->scene()->itemsBoundingRect());
    }
}


bool App::SceneZoom::eventFilter(QObject * object, QEvent * event)
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
                m_oldZoomFactor = factor;
                return true;
            }
        }
    }       
    return false;
}
