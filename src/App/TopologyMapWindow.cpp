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
    if (!m_tabs.empty()) {
        QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), "../../../saves", tr("Xml files(*.xml)"));
        QFile file(filename);

        if (filename.length() == 0) {
            return;
        }

        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            return;
        }

        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];        
        currentTab->getTopologyMap().saveElements(file, currentTab->getName());
    }
}

void TopologyMapWindow::saveFile()
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];        
        
        QString filepath = ("../../../saves/" + currentTab->getName() + ".xml").c_str();
        QFile file(filepath);

        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            return;
        }
        currentTab->getTopologyMap().saveElements(file, currentTab->getName());
    }
}

void TopologyMapWindow::loadSceneFromFile()
{
    if (!m_tabs.empty()) {
        QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../saves", tr("file (*.xml *.mdef)"));
        if (filename.length() == 0) {
            return;
        }
        QFile file(filename);
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
        currentTab->getTopologyMap().loadElements(file, currentTab->getName());
    }
}

void TopologyMapWindow::changePerspectiveToTop()
{
    if (!m_tabs.empty()) {
        Perspective::TopPerspective top;
        auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());            
        auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

        
        scene->setViewableHeight(size().height());
        scene->setViewableWidth(size().width());

        scene->changePerspective(&top);
        view->setSceneRect(scene->itemsBoundingRect());
    }
}
void TopologyMapWindow::changePerspectiveToSide()
{
    if (!m_tabs.empty()) {


        Perspective::SidePerspective side;
        auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
        auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());
        scene->setViewableHeight(size().height());
        scene->setViewableWidth(size().width());

        scene->changePerspective(&side);
        view->setSceneRect(scene->itemsBoundingRect());
    }
}

void TopologyMapWindow::changePerspectiveToFront()
{
    if (!m_tabs.empty()) {
        Perspective::FrontPerspective front;
        auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
        auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

        scene->setViewableHeight(size().height());
        scene->setViewableWidth(size().width());

        scene->changePerspective(&front);
        view->setSceneRect(scene->itemsBoundingRect());
    }
}

void TopologyMapWindow::changePerspectiveCircle()
{
    if (!m_tabs.empty()) {
        auto currentTab = dynamic_cast<TopologyMapTab*>(m_ui->tabWidget->currentWidget());
        auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
        auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

        Perspective::CirclePerspective circle(currentTab->getTopologyMap().getDataModel());
        scene->setViewableHeight(size().height());
        scene->setViewableWidth(size().width());

        scene->changePerspective(&circle);
        view->setSceneRect(scene->itemsBoundingRect());
    }
}

void TopologyMapWindow::changePerspectiveForceDirected()
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
        auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
        auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());

        Perspective::ForceDirectedPerspective force(currentTab->getTopologyMap().getDataModel());
        scene->setViewableHeight(size().height());
        scene->setViewableWidth(size().width());

        scene->changePerspective(&force);

        view->setSceneRect(scene->itemsBoundingRect());
    }
}

void TopologyMapWindow::displayLegend(bool checked)
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];    
        currentTab->toggleLegend();
    }
}

void TopologyMapWindow::displayInfoPanel(bool checked)
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];        
        currentTab->toggleInfoPanel();
    }
}

void TopologyMapWindow::openSearchWindow()
{    
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];    
        m_searchManager->setMechanism(currentTab->getTopologyMap().getGraphicModel());
        m_searchWindow->show();
    }
}

void TopologyMapWindow::displayMotionBodyName(bool checked)
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
        currentTab->getTopologyMap().displayElementName(DataModel::ElementType::MotionBody, checked);
    }
}

void TopologyMapWindow::displayJointName(bool checked)
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
        currentTab->getTopologyMap().displayElementName(DataModel::ElementType::Joint, checked);
    }
}

void TopologyMapWindow::displayConnectorName(bool checked)
{
    if (!m_tabs.empty()) {
        auto currentTab = m_tabs[m_ui->tabWidget->currentIndex()];
        currentTab->getTopologyMap().displayElementName(DataModel::ElementType::Connector, checked);
    }
}

void TopologyMapWindow::closeTab(int index)
{
    auto widget = m_ui->tabWidget->widget(index);
    m_tabs.erase(m_tabs.begin() + index);
    widget->deleteLater();
}

void TopologyMapWindow::compareModels()
{
    if (!m_tabs.empty()) {
        m_compareWindow->setTabs(m_tabs);
        m_compareWindow->initComboBoxes();
        m_compareWindow->show();
    }
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
    auto filename = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../resources", tr("file (*.xml *.mdef)"));
    if (filename.length() == 0) {
        return;
    }

    TopologyMap map;
    
    QFile file(filename);
    map.openElements(file);

    QFileInfo fileInfo(file.fileName());
    std::string modelName = fileInfo.fileName().toStdString();
    
    auto tab = std::make_shared<TopologyMapTab>(map, modelName);
    m_tabs.push_back(tab);
    m_ui->tabWidget->addTab(tab->getView(),tab->getName().c_str());
    m_ui->tabWidget->setCurrentIndex(m_ui->tabWidget->count() - 1);

    changePerspectiveToSide();        

    try {
        QString savePath = ("../../../saves/" + tab->getName() + ".xml").c_str();
        QFile file(savePath);
        
        tab->getTopologyMap().loadElements(file, tab->getName()); 
        auto view = dynamic_cast<TopologyMapView*>(m_ui->tabWidget->currentWidget());
        auto scene = dynamic_cast<GV::TopologyMapScene*>(view->scene());
        view->setSceneRect(scene->itemsBoundingRect());
        
    } catch (...) {
        return;
    }
}