#pragma once
#include <qmenu.h>
#include <memory>
#include <qgraphicssceneevent.h>

namespace DataModel
{
    class Element;
}

namespace GM
{
    class Element;
}

namespace GV
{
    class ElementRightClickMenu :public QMenu
    {
        Q_OBJECT
    public:
        ElementRightClickMenu(std::shared_ptr<GM::Element> elementGraphicModel);
        void processEvent(QGraphicsSceneContextMenuEvent *event);

    signals:
        void sentData(std::shared_ptr<DataModel::Element> elementData);

    protected slots:
        void resetColor();
        void changeColor();
        virtual void showInfo();

    private:
        std::shared_ptr<GM::Element> m_elementModel;

        QAction* m_resetColor;
        QAction* m_changeColorAction;
        QAction* m_showInfo;
        QAction* m_selectedAction;
    };
}