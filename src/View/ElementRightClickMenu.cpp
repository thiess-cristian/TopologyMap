#include "ElementRightClickMenu.h"
#include <qcolor.h>
#include <qcolordialog.h>
#include <iostream>
#include "GraphicElement.h"

ElementRightClickMenu::ElementRightClickMenu(GraphicElement& element):m_element(element)
{    
    m_showInfo = addAction("Show info");
    m_resetColor = addAction("Reset color");
    m_changeColorAction = addAction("Change color");
    
    QObject::connect(m_showInfo, &QAction::triggered, this, &ElementRightClickMenu::showInfo);
    QObject::connect(m_changeColorAction, &QAction::triggered, this, &ElementRightClickMenu::changeColor);
    QObject::connect(m_resetColor, &QAction::triggered, this, &ElementRightClickMenu::resetColor);
}

void ElementRightClickMenu::processEvent(QGraphicsSceneContextMenuEvent * event)
{
    m_selectedAction = exec(event->screenPos());
}

void ElementRightClickMenu::resetColor()
{
    m_element.resetColor();
}

void ElementRightClickMenu::changeColor()
{
    QColor newColor = QColorDialog::getColor(QColor(),this,"select color", QColorDialog::ShowAlphaChannel);

    m_element.setColor(newColor);
}

void ElementRightClickMenu::showInfo()
{
    emit sentData(m_element);
}
