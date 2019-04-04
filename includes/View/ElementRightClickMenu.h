#pragma once

#include <qmenu.h>
#include <qaction.h>
#include <memory>
#include <qgraphicssceneevent.h>
#include <map>

class GraphicElement;

class ElementRightClickMenu:public QMenu
{
    Q_OBJECT
public:
    ElementRightClickMenu(GraphicElement& element);
    void processEvent(QGraphicsSceneContextMenuEvent *event);

signals:
    void sentData(GraphicElement& element);

protected slots:    
    void resetColor();
    void changeColor();    
    virtual void showInfo();

protected:
    GraphicElement& m_element;

    QAction* m_resetColor;
    QAction* m_changeColorAction;
    QAction* m_showInfo;
    QAction* m_selectedAction;
};