#include "App\TopologyMapWindow.h"
#include "App\SceneZoom.h"
#include "App\SearchManager.h"
#include "App\SearchWindow.h"
#include "App\CompareWindow.h"
#include "App\TopologyMapTab.h"
#include "App\TopologyMapView.h"
#include "ui_TopologyMapWindow.h"

#include "Panel\InfoPanel.h"
#include "Panel\LegendPanel.h"

#include "GraphicView\TopologyMapScene.h"

#include "Perspective\SidePerspective.h"
#include "Perspective\TopPerspective.h"
#include "Perspective\FrontPerspective.h"
#include "Perspective\CirclePerspective.h"
#include "Perspective\ForceDirectedPerspective.h"

#include <GraphicView\TopologyMapScene.h>
#include <DataHandler\DocumentParser.h>
#include <qaction.h>
#include <qfiledialog.h>

using namespace App;

TopologyMapWindow::TopologyMapWindow(QWidget *parent) :QMainWindow(parent)
{
    m_ui = std::make_unique<Ui_TopologyMapWindow>();
    m_ui->setupUi(this);

    QObject::connect(m_ui->actionOpen,          &QAction::triggered, this, &TopologyMapWindow::openFile);
    QObject::connect(m_ui->actionSave_as,       &QAction::triggered, this, &TopologyMapWindow::saveAsFile);
    QObject::connect(m_ui->actionSave,          &QAction::triggered, this, &TopologyMapWindow::saveFile);
    QObject::connect(m_ui->actionLoad,          &QAction::triggered, this, &TopologyMapWindow::loadSceneFromFile);

    QObject::connect(m_ui->actionLegend,        &QAction::triggered, this, &TopologyMapWindow::displayLegend);
    QObject::connect(m_ui->actionInformation,   &QAction::triggered, this, &TopologyMapWindow::displayInfoPanel);
    QObject::connect(m_ui->actionSearch,        &QAction::triggered, this, &TopologyMapWindow::openSearchWindow);

    QObject::connect(m_ui->actionFront,         &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToFront);
    QObject::connect(m_ui->actionSide,          &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToSide);
    QObject::connect(m_ui->actionTop,           &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToTop);
    QObject::connect(m_ui->actionCircle,        &QAction::triggered, this, &TopologyMapWindow::changePerspectiveCircle);
    QObject::connect(m_ui->actionForce_Directed,&QAction::triggered, this, &TopologyMapWindow::changePerspectiveForceDirected);

    QObject::connect(m_ui->actionMotion_body,   &QAction::triggered, this, &TopologyMapWindow::displayMotionBodyName);
    QObject::connect(m_ui->actionJoint,         &QAction::triggered, this, &TopologyMapWindow::displayJointName);
    QObject::connect(m_ui->actionConnector,     &QAction::triggered, this, &TopologyMapWindow::displayConnectorName);

    QObject::connect(m_ui->actionCompare,       &QAction::triggered, this, &TopologyMapWindow::compareModels);
    QObject::connect(m_ui->actionReset_colors,  &QAction::triggered, this, &TopologyMapWindow::resetColors);

    m_searchManager = std::make_shared<SearchManager>();
    m_searchWindow = std::make_unique<SearchWindow>(m_searchManager);

    m_compareWindow = std::make_unique<CompareWindow>(m_ui->tabWidget);

    m_ui->tabWidget->setTabsClosable(true);
    QObject::connect(m_ui->tabWidget, &QTabWidget::tabCloseRequested, this, &TopologyMapWindow::closeTab);
}

TopologyMapWindow::~TopologyMapWindow()
{}

void TopologyMapWindow::saveAsFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), "../../../saves", tr("Xml files(*.xml)"));
    QFile file(filename);

    if (filename.length() == 0) {
        return;
    }

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    m_topologyMap.saveElements(file, m_filename.toStdString());    
}

void TopologyMapWindow::saveFile()
{
    if (m_filename.length() == 0) {
        return;
    }

    QString filepath = "../../../saves/" + m_filename + ".xml";

    QFile file(filepath);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    m_topologyMap.saveElements(file, m_filename.toStdString());
}

void TopologyMapWindow::loadSceneFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../saves", tr("file (*.xml *.mdef)"));
    if (filename.length() == 0) {
        return;
    }

    QFile file(filename);

    m_topologyMap.loadElements(file, m_filename.toStdString());
}

void TopologyMapWindow::changePerspectiveToTop()
{
    Perspective::TopPerspective top;  
    auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
    auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());
    scene->setViewableHeight(size().height());
    scene->setViewableWidth(size().width());

    scene->changePerspective(&top);
}

void TopologyMapWindow::changePerspectiveToSide()
{
    Perspective::SidePerspective side;
    
    auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
    auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

    scene->setViewableHeight(size().height());
    scene->setViewableWidth(size().width());

    scene->changePerspective(&side);
}

void TopologyMapWindow::changePerspectiveToFront()
{
    Perspective::FrontPerspective front;
    auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
    auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

    scene->setViewableHeight(size().height());
    scene->setViewableWidth(size().width());

    scene->changePerspective(&front);
}

void TopologyMapWindow::changePerspectiveCircle()
{
    auto currentTab = dynamic_cast<TopologyMapTab*>(m_ui->tabWidget->currentWidget());
    auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
    auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

    Perspective::CirclePerspective circle(currentTab->getTopologyMap().getDataModel());
    scene->setViewableHeight(size().height());
    scene->setViewableWidth(size().width());

    scene->changePerspective(&circle);

}

void TopologyMapWindow::changePerspectiveForceDirected()
{

    auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
    auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
    auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

    Perspective::ForceDirectedPerspective force(currentTab->getTopologyMap().getDataModel());
    scene->setViewableHeight(size().height());
    scene->setViewableWidth(size().width());

    scene->changePerspective(&force);
}

void TopologyMapWindow::displayLegend(bool checked)
{
    auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
    currentTab->displayLegend(checked);
}

void TopologyMapWindow::displayInfoPanel(bool checked)
{
    auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
    currentTab->displayInfoPanel(checked);
}

void TopologyMapWindow::openSearchWindow()
{
    //m_searchManager->setGraphicMechanism(m_manager.getGraphicMechanism());
    m_searchManager->setMechanism(m_topologyMap.getGraphicModel());    
    m_searchWindow->show();
}

void TopologyMapWindow::displayMotionBodyName(bool checked)
{
    m_topologyMap.displayElementName(DataModel::ElementType::MotionBody, checked);
}

void TopologyMapWindow::displayJointName(bool checked)
{
    m_topologyMap.displayElementName(DataModel::ElementType::Joint, checked);
}

void TopologyMapWindow::displayConnectorName(bool checked)
{
    m_topologyMap.displayElementName(DataModel::ElementType::Connector, checked);
}

void TopologyMapWindow::closeTab(int index)
{
    auto widget = m_ui->tabWidget->widget(index);
    m_tabs.erase(m_tabs.begin() + index);
    widget->deleteLater();
}

void TopologyMapWindow::compareModels()
{
    m_compareWindow->setTabs(m_tabs);
    m_compareWindow->initComboBoxes();
    m_compareWindow->show();
}

void TopologyMapWindow::resetColors()
{
    auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
    auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

    scene->resetColors();
    scene->update();
}

void TopologyMapWindow::openFile()
{
    m_filename = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../resources", tr("file (*.xml *.mdef)"));
    if (m_filename.length() == 0) {
        return;
    }

    TopologyMap map;
    
    QFile file(m_filename);
    map.openElements(file);

    QFileInfo fileInfo(file.fileName());
    std::string modelName = fileInfo.fileName().toStdString();
    
    auto tab = std::make_shared<TopologyMapTab>(map, modelName);
    m_tabs.push_back(tab);
    m_ui->tabWidget->addTab(tab->getView(),tab->getName().c_str());
    m_ui->tabWidget->setCurrentIndex(m_ui->tabWidget->count() - 1);

    changePerspectiveToSide();
        
    //m_filename = filename.substr(0, lastindex).c_str();

    try {
        QString savePath = "../../../saves/" + m_filename + ".xml";
        QFile file(savePath);
        
        //m_topologyMap.loadElements(file, m_filename.toStdString());
    } catch (...) {
        return;
    }
}