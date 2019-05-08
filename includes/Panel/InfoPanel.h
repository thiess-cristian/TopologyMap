#pragma once
#include <qwidget.h>
#include <memory>

class QTabWidget;
class QGraphicsView;
class GraphicElement;
class MotionBody;
class Connector;
class Joint;

namespace DataModel
{
    class Element;
    class MotionBody;
    class Connector;
    class Joint;
}

namespace Panel
{
    class InfoPanel :public QWidget
    {
        Q_OBJECT
    public:
        InfoPanel(QGraphicsView* view);
        void display(bool checked);

    public slots:
        void closeTab(int index);
        void addInfoTab(std::shared_ptr<DataModel::Element> element);

    private:
        void addMotionBodyInfo(std::shared_ptr<DataModel::MotionBody> motionBodyModel);
        void addConnectorInfo(std::shared_ptr<DataModel::Connector> connectorModel);
        void addJointInfo(std::shared_ptr<DataModel::Joint> jointModel);
        QTabWidget* m_tab;
    };
}
