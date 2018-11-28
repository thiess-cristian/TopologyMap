#include "TopologyMapWindow.h"
#include "ui_TopologyMapWindow.h"
#include "TopologyMapScene.h"

#include <qfiledialog.h>

TopologyMapWindow::TopologyMapWindow(QWidget *parent):QMainWindow(parent)
{
    m_ui=std::make_unique<Ui_TopologyMapWindow>();
    m_ui->setupUi(this);

    m_scene = new TopologyMapScene();
    m_ui->graphicsView->setScene(m_scene);

    QObject::connect(m_ui->actionOpen, &QAction::triggered, this, &TopologyMapWindow::openFile);
    QObject::connect(m_ui->actionFront, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToFront);
    QObject::connect(m_ui->actionSide, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToSide);
    QObject::connect(m_ui->actionTop, &QAction::triggered, this, &TopologyMapWindow::changePerspectiveToTop);

}

TopologyMapWindow::~TopologyMapWindow()
{}

void TopologyMapWindow::changePerspectiveToTop()
{
    m_manager.addElementsToScene(m_scene, Perspective::TOP);
   // m_ui->graphicsView->fitInView(m_scene->sceneRect());
}

void TopologyMapWindow::changePerspectiveToSide()
{
    m_manager.addElementsToScene(m_scene, Perspective::SIDE);
    double factor = std::max(size().width() / m_scene->sceneRect().width(), size().height() / m_scene->sceneRect().height());
    m_ui->graphicsView->scale(factor, factor);
    //m_ui->graphicsView->fitInView(m_scene->sceneRect());
}

void TopologyMapWindow::changePerspectiveToFront()
{
    m_manager.addElementsToScene(m_scene, Perspective::FRONT);
   // m_ui->graphicsView->fitInView(m_scene->sceneRect());
}

void TopologyMapWindow::openFile()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("file (*.xml *.mdef)"));
    if (imagePath.length()==0) {
        return;
    }

    QFile file(imagePath);
    m_manager.loadElements(file);
    changePerspectiveToSide();
}
