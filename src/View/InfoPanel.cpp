#include "InfoPanel.h"
#include "GraphicElement.h"
#include "MotionBody.h"
#include "Joint.h"
#include "Connector.h"
#include "LinkAtachment.h"
#include "JointStringToEnum.h"

#include <qgraphicsview.h>
#include <qtableview.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qstringlistmodel.h>


#include <ui_MotionBodyInfo.h>
#include <ui_JointInfo.h>
#include <ui_ConnectorInfo.h>



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
    
    std::unique_ptr<Ui_MotionBodyInfo> ui= std::make_unique<Ui_MotionBodyInfo>();
    ui->setupUi(content);
    ui->labelNameContent->setText(motionBodyModel->getName().c_str());
    ui->labelXCoordContent->setText(QString::number(motionBodyModel->getOrigin().getX()));
    ui->labelYCoordContent->setText(QString::number(motionBodyModel->getOrigin().getY()));
    ui->labelZCoordContent->setText(QString::number(motionBodyModel->getOrigin().getZ()));
    
    QStringListModel *model = new QStringListModel(content);
    QStringList list;    
    ui->listViewLinkAtachments->setEditTriggers(QAbstractItemView::NoEditTriggers);
     
    auto linkAtachments = motionBodyModel->getLinkAtachments();
    for (const auto linkAtachment : linkAtachments) {
        list << linkAtachment->getLink().getName().c_str();        
    }    
    
    model->setStringList(list);
    ui->listViewLinkAtachments->setModel(model);

    m_tab->addTab(content, motionBodyModel->getName().c_str());
}

void InfoPanel::addConnectorInfo(std::shared_ptr<Connector> connectorModel)
{
    QWidget* content = new QWidget(m_tab);
    
    std::unique_ptr<Ui_ConnectorInfo> ui = std::make_unique<Ui_ConnectorInfo>();
    ui->setupUi(content);
        
    ui->labelNameContent->setText(connectorModel->getName().c_str());

    ui->labelActionContent->setText(connectorModel->getAction().getName().c_str());
    ui->labelBaseContent->setText(connectorModel->getBase().getName().c_str());

    m_tab->addTab(content, connectorModel->getName().c_str());
}

void InfoPanel::addJointInfo(std::shared_ptr<Joint> jointModel)
{
    QWidget* content = new QWidget(m_tab);
    JointStringToEnum enumConv;
    std::unique_ptr<Ui_JointInfo> ui = std::make_unique<Ui_JointInfo>();
    ui->setupUi(content);
    ui->labelNameContent->setText(jointModel->getName().c_str());
    std::string type;
    type = enumConv.getString(jointModel->getType());
    ui->labelTypeContent->setText(type.c_str());

    ui->labelActionContent->setText(jointModel->getAction().getName().c_str());
    ui->labelBaseContent->setText(jointModel->getBase().getName().c_str());

    m_tab->addTab(content, jointModel->getName().c_str());
}

void InfoPanel::closeTab(int index)
{      
    auto widget=m_tab->widget(index);
    widget->deleteLater();
}
