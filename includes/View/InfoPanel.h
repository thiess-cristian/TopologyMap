#pragma once
#include <qwidget.h>

class QTabWidget;
class QGraphicsView;
class GraphicElement;

class InfoPanel :public QWidget
{
    Q_OBJECT
public:
    InfoPanel(QGraphicsView* view);
    void display(bool checked);

public slots:
    void closeTab(int index);
    void addInfoTab(GraphicElement& element);

private:
    QTabWidget* m_tab;
};
