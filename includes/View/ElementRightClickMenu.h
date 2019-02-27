#pragma once

#include <qmenu.h>
#include <qaction.h>
#include <memory>
#include <qgraphicssceneevent.h>

#include "GraphicElement.h"

class ElementRightClickMenu:public QMenu
{
    Q_OBJECT
public:
    ElementRightClickMenu(GraphicElement& element);
    void processEvent(QGraphicsSceneContextMenuEvent *event);

protected slots:    
    void resetColor();
    void changeColor();
    void deleteItem();

private:

    GraphicElement& m_element;

    QAction* m_resetColor;
    QAction* m_changeColorAction;
    QAction* m_removeAction;
    QAction* m_selectedAction;
};