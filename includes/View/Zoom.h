#pragma once
#include <qobject.h>
#include <qpoint.h>

class QGraphicsView;
class ElementsManager;

class Zoom : public QObject
{
    Q_OBJECT
public:
    Zoom(QGraphicsView* view,ElementsManager* manager);
    void setZoomFactor(double value);

private:
    void zoom(double factor);
    bool eventFilter(QObject* object, QEvent* event);
    QGraphicsView* m_view;
    ElementsManager* m_manager;
    double m_zoomFactor;
    QPointF m_targetScenePos;
    QPointF m_targetViewportPos;

signals:
    void zoomed();
};