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
    QObject::connect(m_ui->actionFront, &QAction::triggered, this, &TopologyMapWindow::changePerspective);
    QObject::connect(m_ui->actionSide, &QAction::triggered, this, &TopologyMapWindow::changePerspective);
    QObject::connect(m_ui->actionTop, &QAction::triggered, this, &TopologyMapWindow::changePerspective);

}

TopologyMapWindow::~TopologyMapWindow()
{}

void TopologyMapWindow::changePerspective()
{
    QObject* sender=QObject::sender();

    std::string name=sender->objectName().toStdString();

    if (name == "actionTop") {
        m_manager.addElementsToScene(m_scene, Perspective::TOP);
    } else if (name == "actionSide") {
        m_manager.addElementsToScene(m_scene, Perspective::SIDE);
    } else if (name == "actionFront") {
        m_manager.addElementsToScene(m_scene, Perspective::FRONT);

    }

}

void TopologyMapWindow::openFile()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("file (*.xml *.mdef)"));
    if (imagePath.length()==0) {
        return;
    }

    QFile file(imagePath);
    m_manager.loadElements(file);
    m_manager.addElementsToScene(m_scene,Perspective::SIDE);
}
