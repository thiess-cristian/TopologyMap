#include "App\TopologyMapWindow.h"
#include "App\SceneZoom.h"
#include "App\SearchManager.h"
#include "App\SearchWindow.h"
#include "ui_TopologyMapWindow.h"

#include "Panel\InfoPanel.h"
#include "Panel\LegendPanel.h"

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

    m_scene = new GV::TopologyMapScene();
    m_ui->graphicsView->setScene(m_scene);

    QObject::connect(m_ui->actionOpen, &QAction::triggered, this, &TopologyMapWindow::openFile);
    QObject::connect(m_ui->actionSave_as, &QAction::triggered, this, &TopologyMapWindow::saveAsFile);
    QObject::connect(m_ui->actionSave, &QAction::triggered, this, &TopologyMapWindow::saveFile);
    QObject::connect(m_ui->actionLoad, &QAction::triggered, this, &TopologyMapWindow::loadSceneFromFile);

    QObject::connect(m_ui->actionLegend, &QAction::triggered, this, &TopologyMapWindow::displayLegend);
    QObject::connect(m_ui->actionInformation, &QAction::triggered, this, &TopologyMapWindow::displayInfoPanel);
    QObject::connect(m_ui->actionSearch, &QAction::triggered, this, &TopologyMapWindow::openSearchWindow);

    QObject::connect(m_ui->actionFront, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToFront);
    QObject::connect(m_ui->actionSide, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToSide);
    QObject::connect(m_ui->actionTop, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToTop);
    QObject::connect(m_ui->actionCircle, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveCircle);
    QObject::connect(m_ui->actionForce_Directed, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveForceDirected);

    QObject::connect(m_ui->actionMotion_body, &QAction::triggered, this, &TopologyMapWindow::displayMotionBodyName);
    QObject::connect(m_ui->actionJoint, &QAction::triggered, this, &TopologyMapWindow::displayJointName);
    QObject::connect(m_ui->actionConnector, &QAction::triggered, this, &TopologyMapWindow::displayConnectorName);

    m_ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    m_ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    m_zoom = std::make_unique<SceneZoom>(m_ui->graphicsView);

    m_legend = std::make_unique<Panel::LegendPanel>(m_ui->graphicsView);
    m_infoPanel = std::make_unique<Panel::InfoPanel>(m_ui->graphicsView);

    m_searchManager = std::make_shared<SearchManager>();
    m_searchWindow = std::make_unique<SearchWindow>(m_searchManager);
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

    m_scene->setViewableHeight(size().height());
    m_scene->setViewableWidth(size().width());

    m_scene->changePerspective(&top);
}

void TopologyMapWindow::changePerspectiveToSide()
{
    Perspective::SidePerspective side;

    m_scene->setViewableHeight(size().height());
    m_scene->setViewableWidth(size().width());

    m_scene->changePerspective(&side);
}

void TopologyMapWindow::changePerspectiveToFront()
{
    Perspective::FrontPerspective front;

    m_scene->setViewableHeight(size().height());
    m_scene->setViewableWidth(size().width());

    m_scene->changePerspective(&front);
}

void TopologyMapWindow::changePerspectiveCircle()
{
    Perspective::CirclePerspective circle(m_topologyMap.getDataModel());

    m_scene->setViewableHeight(size().height());
    m_scene->setViewableWidth(size().width());

    m_scene->changePerspective(&circle);

}

void TopologyMapWindow::changePerspectiveForceDirected()
{
    Perspective::ForceDirectedPerspective force(m_topologyMap.getDataModel());

    m_scene->setViewableHeight(size().height());
    m_scene->setViewableWidth(size().width());

    m_scene->changePerspective(&force);
}

void TopologyMapWindow::displayLegend(bool checked)
{
    m_legend->display(checked);
}

void TopologyMapWindow::displayInfoPanel(bool checked)
{
    m_infoPanel->display(checked);
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

void TopologyMapWindow::openFile()
{
    m_filename = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../resources", tr("file (*.xml *.mdef)"));
    if (m_filename.length() == 0) {
        return;
    }

    QFile file(m_filename);

    DataHandler::DocumentParser p;
    p.parseFile(file);


    m_topologyMap.openElements(file);
    m_zoom->setMechanism(m_topologyMap.getGraphicModel());

    m_scene->addElements(m_topologyMap.getGraphicModel());
    m_scene->setInfoPanelRelations(m_infoPanel);

    changePerspectiveToSide();
    
    QFileInfo fileInfo(m_filename);
    std::string filename = fileInfo.fileName().toStdString();

    size_t lastindex = filename.find_last_of(".");
    m_filename = filename.substr(0, lastindex).c_str();

    try {
        QString savePath = "../../../saves/" + m_filename + ".xml";
        QFile file(savePath);
        
        m_topologyMap.loadElements(file, m_filename.toStdString());
    } catch (...) {
        return;
    }
}