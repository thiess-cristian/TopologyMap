#pragma once
#include <qwidget.h>

class QFrame;
class QGraphicsView;
class QTabWidget;
class QFormLayout;

namespace Panel
{
    class LegendPanel :public QWidget
    {
    public:
        LegendPanel(QGraphicsView* view);

        void display(bool checked);

    private:
        QFormLayout* createJointsLayout();
        QFormLayout* createConnectorsLayout();

        QTabWidget* m_tab;
        QWidget* m_joints;
        QWidget* m_connectors;
    };
}