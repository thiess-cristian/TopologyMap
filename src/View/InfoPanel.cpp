#include "InfoPanel.h"
#include "GraphicElement.h"
#include "MotionBody.h"
#include "Joint.h"
#include "Connector.h"

#include <qgraphicsview.h>
#include <qtableview.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qwidget.h>
#include <qlayout.h>
#include <sstream>


InfoPanel::InfoPanel(QGraphicsView * view)
{
    m_tab = new QTabWidget(this);

    m_tab->setFixedWidth(170);
    m_tab->setFixedHeight(200);
    
    auto layout =view->layout();
    
    layout->addWidget(m_tab);

    m_tab->hide();
        
    m_tab->setTabsClosable(true);
}

void InfoPanel::display(bool checked)
{
    if (checked) {
        m_tab->show();
    } else {
        m_tab->hide();
    }
}

void InfoPanel::addInfoTab(GraphicElement& element)
{
    auto motionBodyModel = std::dynamic_pointer_cast<MotionBody>(element.getElementModel());
    auto connectorModel = std::dynamic_pointer_cast<Connector>(element.getElementModel());
    auto jointModel = std::dynamic_pointer_cast<Joint>(element.getElementModel());

    if (motionBodyModel != nullptr) {
        addMotionBodyInfo(motionBodyModel);
    } else if (connectorModel != nullptr) {
        addConnectorInfo(connectorModel);
    } else if (jointModel != nullptr) {
        addJointInfo(jointModel);
    }

    QObject::connect(m_tab, &QTabWidget::tabCloseRequested, this, &InfoPanel::closeTab);
}

void InfoPanel::addMotionBodyInfo(std::shared_ptr<MotionBody> motionBodyModel)
{
    QWidget* content = new QWidget(m_tab);
    QFormLayout* layout = new QFormLayout(content);
    QLabel* nameLabel = new QLabel("name:", content);

    QLabel* textLabel = new QLabel(motionBodyModel->getName().c_str(), content);
    layout->addRow(nameLabel, textLabel);
    
    m_tab->addTab(content, motionBodyModel->getName().c_str());
}

void InfoPanel::addConnectorInfo(std::shared_ptr<Connector> connectorModel)
{

    QWidget* content = new QWidget(m_tab);
    QFormLayout* layout = new QFormLayout(content);
    QLabel* nameLabel = new QLabel("name:", content);

    QLabel* textLabel = new QLabel(connectorModel->getName().c_str(), content);
    layout->addRow(nameLabel, textLabel);

    

    m_tab->addTab(content, connectorModel->getName().c_str());
}

void InfoPanel::addJointInfo(std::shared_ptr<Joint> jointModel)
{

    QWidget* content = new QWidget(m_tab);
    QFormLayout* layout = new QFormLayout(content);
    QLabel* nameLabel = new QLabel("name:", content);

    QLabel* textLabel = new QLabel(jointModel->getName().c_str(), content);
    layout->addRow(nameLabel, textLabel);

    m_tab->addTab(content, jointModel->getName().c_str());
}

void InfoPanel::closeTab(int index)
{      
    auto widget=m_tab->widget(index);
    widget->deleteLater();
}
