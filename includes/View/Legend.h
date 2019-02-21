#pragma once


class QFrame;
class QGraphicsView;
class QTabWidget;
class QFormLayout;

class Legend
{
public:
    Legend(QGraphicsView* view);

    void display(bool checked);

private:

    QFormLayout* createJointsLayout();
    QFormLayout* createConnectorsLayout();

    QTabWidget* m_tab;
};