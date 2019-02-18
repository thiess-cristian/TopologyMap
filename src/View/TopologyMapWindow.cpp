#include "TopologyMapWindow.h"
#include "ui_TopologyMapWindow.h"
#include "TopologyMapScene.h"
#include "TopPerspective.h"
#include "SidePerspective.h"
#include "FrontPerspective.h"
#include "CirclePerspective.h"
#include "ForceDirectedPerspective.h"
#include "Zoom.h"

#include <qfiledialog.h>

TopologyMapWindow::TopologyMapWindow(QWidget *parent):QMainWindow(parent)
{
    m_ui=std::make_unique<Ui_TopologyMapWindow>();
    m_ui->setupUi(this);

    m_scene = new TopologyMapScene();
    m_ui->graphicsView->setScene(m_scene);

    QObject::connect(m_ui->actionOpen, &QAction::triggered, this, &TopologyMapWindow::openFile);
    QObject::connect(m_ui->actionSave, &QAction::triggered, this, &TopologyMapWindow::saveFile);
    QObject::connect(m_ui->actionFront, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToFront);
    QObject::connect(m_ui->actionSide, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToSide);
    QObject::connect(m_ui->actionTop, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToTop);
    QObject::connect(m_ui->actionCircle, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveCircle);
    QObject::connect(m_ui->actionForce_Directed, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveForceDirected);
    
    m_ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    m_ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    m_zoom = std::make_unique<Zoom>(m_ui->graphicsView, &m_manager);
}

TopologyMapWindow::~TopologyMapWindow()
{}

void TopologyMapWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save file"),"../../../saves",tr("Xml files(*.xml)"));
    QFile file(filename);

    if (filename.length() == 0) {
        return;
    }

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    m_manager.saveElements(file);
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

void TopologyMapWindow::openFile()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "../../../resources", tr("file (*.xml *.mdef)"));
    if (imagePath.length()==0) {
        return;
    }

    QFile file(imagePath);
    m_manager.openElements(file);
    m_manager.setWindowSize(size().height()-100,size().width()-100);
    m_manager.addElementsToScene(m_scene);
}
