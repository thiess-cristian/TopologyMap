#pragma once
#include <qwidget.h>
#include <memory>

class QTabWidget;
class QGraphicsView;
class GraphicElement;
class MotionBody;
class Connector;
class Joint;

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
    void addMotionBodyInfo(std::shared_ptr<MotionBody> motionBodyModel);
    void addConnectorInfo(std::shared_ptr<Connector> connectorModel);
    void addJointInfo(std::shared_ptr<Joint> jointModel);
    QTabWidget* m_tab;
};
