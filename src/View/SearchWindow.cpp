#include "SearchWindow.h"
#include "ui_SearchWindow.h"
#include "SearchRequirements.h"

#include <qcolor.h>
#include <qcolordialog.h>

SearchWindow::SearchWindow(QWidget * parent):QWidget(parent)
{
    m_ui = std::make_unique<Ui_SearchWindow>();
    m_ui->setupUi(this);

    QObject::connect(m_ui->pushButtonSearch, &QPushButton::clicked, this, &SearchWindow::searchClicked);
    QObject::connect(m_ui->pushButtonSelectColor, &QPushButton::clicked, this, &SearchWindow::selectColorClicked);
    QObject::connect(m_ui->pushButtonReset, &QPushButton::clicked, this, &SearchWindow::resetClicked);
}

SearchWindow::~SearchWindow()
{}

void SearchWindow::searchClicked()
{
    SearchRequirements searchRequirements;

    searchRequirements.searchText = m_ui->lineEdit->text().toStdString();
    searchRequirements.motionBodyCheck = m_ui->checkBoxMotionBody->isChecked();
    searchRequirements.jointCheck = m_ui->checkBoxJoint->isChecked();
    searchRequirements.connectorCheck = m_ui->checkBoxConnector->isChecked();
    searchRequirements.matchCase = m_ui->checkBoxMatchCase->isChecked();
    searchRequirements.matchWhole = m_ui->checkBoxMatchWhole->isChecked();
    searchRequirements.regEx = m_ui->checkBoxRegEx->isChecked();

    emit sendSearchRequirements(searchRequirements);
    
    close();
}

void SearchWindow::resetClicked()
{
    emit reset();
    close();
}

void SearchWindow::selectColorClicked()
{
    QColor initial(0, 255, 0);
    QColor color=QColorDialog::getColor(initial, this, "select color");

    emit changeColor(color);
}
