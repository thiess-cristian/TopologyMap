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
        SceneZoom(QGraphicsView* view, GM::Mechanism& mechansim);
    signals:
        void zoomed();

    private:
        void zoom(double factor);
        bool eventFilter(QObject* object, QEvent* event);

        QGraphicsView* m_view;
        GM::Mechanism& m_mechansim;

        double m_zoomFactor;
        QPointF m_targetScenePos;
        QPointF m_targetViewportPos;
    };
}