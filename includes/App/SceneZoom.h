#pragma once
#include <qobject.h>
#include <qpoint.h>
#include <memory>

namespace GM
{
    class Mechanism;
}

class QGraphicsView;

namespace App
{
    class SceneZoom : public QObject
    {
        Q_OBJECT
    public:
        SceneZoom(QGraphicsView* view);
        void setMechanism(std::shared_ptr<GM::Mechanism> mechanism);
    signals:
        void zoomed();

    private:
        void zoom(double factor);
        bool eventFilter(QObject* object, QEvent* event);

        QGraphicsView* m_view;        
        std::shared_ptr<GM::Mechanism> m_mechanism;

        double m_zoomFactor = 1;
        double m_oldZoomFactor = 1;
        QPointF m_targetScenePos;
        QPointF m_targetViewportPos;
        
    };
}