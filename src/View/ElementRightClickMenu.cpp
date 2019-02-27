#include "ElementRightClickMenu.h"
#include <qcolor.h>
#include <qcolordialog.h>

ElementRightClickMenu::ElementRightClickMenu(GraphicElement& element):m_element(element)
{
    m_removeAction = addAction("Remove");
    m_resetColor = addAction("Reset color");
    m_changeColorAction = addAction("Change color");

    QObject::connect(m_removeAction, &QAction::triggered, this, &ElementRightClickMenu::deleteItem);
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

void ElementRightClickMenu::deleteItem()
{
    
}
