#include "GraphicView\ElementRightClickMenu.h"
#include "GraphicModel\Element.h"
#include <qcolor.h>
#include <qcolordialog.h>

using namespace GV;

ElementRightClickMenu::ElementRightClickMenu(std::shared_ptr<GM::Element> elementGraphicModel) :m_elementModel(elementGraphicModel)
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
    m_elementModel->setColor(m_elementModel->DefaultColor);
}

void ElementRightClickMenu::changeColor()
{
    QColor newColor = QColorDialog::getColor(QColor(), this, "Select color", QColorDialog::ShowAlphaChannel);
    m_elementModel->setColor(newColor);
}

void ElementRightClickMenu::showInfo()
{
    emit sentData(m_elementModel->getDataModel());
}