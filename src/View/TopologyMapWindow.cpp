#include "TopologyMapWindow.h"
#include "ui_TopologyMapWindow.h"
#include "TopologyMapScene.h"
#include "TopPerspective.h"
#include "SidePerspective.h"
#include "FrontPerspective.h"

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

void TopologyMapWindow::openFile()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("file (*.xml *.mdef)"));
    if (imagePath.length()==0) {
        return;
    }

    QFile file(imagePath);
    m_manager.loadElements(file);
    m_manager.scaleMechanism(size().height(),size().width());
    m_manager.addElementsToScene(m_scene);
}
