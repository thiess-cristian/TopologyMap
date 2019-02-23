#include "Legend.h"
#include "JointStringToEnum.h"
#include "ConnectorStringToEnum.h"
#include "JointPainterPathCreator.h"
#include "ConnectorPainterPathCreator.h"

#include <qpixmap.h>
#include <qpainter.h>
#include <qimage.h>
#include <qpoint.h>
#include <qlayout.h>
#include <qgraphicsview.h>
#include <qtableview.h>
#include <qlabel.h>
#include <qformlayout.h>

Legend::Legend(QGraphicsView* view)
{   
    m_tab = new QTabWidget(this);
    
    m_tab->setFixedWidth(170);

    m_joints = new QWidget(m_tab);
    m_joints->setLayout(createJointsLayout());

    m_connectors = new QWidget(m_tab);
    m_connectors->setLayout(createConnectorsLayout());

    m_tab->addTab(m_joints, "Joints");
    m_tab->addTab(m_connectors, "Connectors");
    
    QVBoxLayout* layout = new QVBoxLayout(view);
    layout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    layout->addWidget(m_tab);
    
    m_tab->hide();
}

void Legend::display(bool checked)
{
    if (checked) {
        m_tab->show();
    } else {
        m_tab->hide();
    }
}

QFormLayout * Legend::createJointsLayout()
{
    QFormLayout* layout = new QFormLayout(m_joints);
    JointStringToEnum strings;

    for (const auto& name : strings.getStrings()) {
        JointPainterPathCreator pathCreator(name.second);
        QImage image(50,50, QImage::Format_ARGB32);
        QPainterPath path = pathCreator.getPath(QPointF(0,25),QPointF(50,25));
        QPainter painter(&image);

        painter.drawPath(path);
        
        QPixmap pixmap(QPixmap::fromImage(image));

        QLabel* imageLabel = new QLabel();

        imageLabel->setPixmap(pixmap);

        QLabel* textLabel = new QLabel(name.first.c_str());

        layout->addRow(imageLabel, textLabel);
    }
    return layout;
}


QFormLayout * Legend::createConnectorsLayout()
{
    QFormLayout* layout = new QFormLayout(m_connectors);
    ConnectorStringToEnum strings;

    for (const auto& name : strings.getStrings()) {
        ConnectorPainterPathCreator pathCreator(name.second);
        QImage image(50, 50, QImage::Format_ARGB32);
        QPainterPath path = pathCreator.getPath(QPointF(0, 25), QPointF(50, 25));
        QPainter painter(&image);

        painter.setPen(Qt::red);    
        painter.drawPath(path);
        
        QPixmap pixmap(QPixmap::fromImage(image));

        QLabel* imageLabel = new QLabel();
        
        imageLabel->setPixmap(pixmap);

        QLabel* textLabel = new QLabel(name.first.c_str());

        layout->addRow(imageLabel, textLabel);
    }
    return layout;
}
