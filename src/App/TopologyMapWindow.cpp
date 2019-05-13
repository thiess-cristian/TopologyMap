#include "App\TopologyMapWindow.h"
#include "App\SceneZoom.h"
#include "ui_TopologyMapWindow.h"
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

    m_zoom = std::make_unique<SceneZoom>(m_ui->graphicsView, &m_manager);

    m_legend = std::make_unique<Legend>(m_ui->graphicsView);
    m_infoPanel = std::make_unique<InfoPanel>(m_ui->graphicsView);

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

    m_manager.saveElements(file, m_filename.toStdString());
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

    m_manager.saveElements(file, m_filename.toStdString());
}

void TopologyMapWindow::loadSceneFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../saves", tr("file (*.xml *.mdef)"));
    if (filename.length() == 0) {
        return;
    }

    QFile file(filename);

    m_manager.loadElements(file, m_filename.toStdString());
}

void TopologyMapWindow::changePerspectiveToTop()
{
    TopPerspective top;
    m_manager.changePerspective(&top);
}

void TopologyMapWindow::changePerspectiveToSide()
{
    SidePerspective side;
    m_manager.changePerspective(&side);
}

void TopologyMapWindow::changePerspectiveToFront()
{
    FrontPerspective front;
    m_manager.changePerspective(&front);
}

void TopologyMapWindow::changePerspectiveCircle()
{
    CirclePerspective circle(m_manager.getMechanism());
    m_manager.changePerspective(&circle);
}

void TopologyMapWindow::changePerspectiveForceDirected()
{
    ForceDirectedPerspective force(m_manager.getMechanism());
    m_manager.changePerspective(&force);
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
    m_searchManager->setGraphicMechanism(m_manager.getGraphicMechanism());
    m_searchWindow->show();
}

void TopologyMapWindow::displayMotionBodyName(bool checked)
{
    m_manager.displayElementName(ElementType::MotionBody, checked);
}

void TopologyMapWindow::displayJointName(bool checked)
{
    m_manager.displayElementName(ElementType::Joint, checked);
}

void TopologyMapWindow::displayConnectorName(bool checked)
{
    m_manager.displayElementName(ElementType::Connector, checked);
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


    m_manager.openElements(file);
    m_manager.setWindowSize(size().height() - 100, size().width() - 100);
    m_manager.addElementsToScene(m_scene);
    m_manager.setUpInfoPanelRelations(m_infoPanel);

    QFileInfo fileInfo(m_filename);
    std::string filename = fileInfo.fileName().toStdString();

    size_t lastindex = filename.find_last_of(".");
    m_filename = filename.substr(0, lastindex).c_str();

    try {
        QString savePath = "../../../saves/" + m_filename + ".xml";
        QFile file(savePath);

        m_manager.loadElements(file, m_filename.toStdString());
    } catch (...) {
        return;
    }
}