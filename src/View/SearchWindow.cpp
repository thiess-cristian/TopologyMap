#include "SearchWindow.h"
#include "ui_SearchWindow.h"
#include "SearchRequirements.h"

SearchWindow::SearchWindow(QWidget * parent):QWidget(parent)
{
    m_ui = std::make_unique<Ui_SearchWindow>();
    m_ui->setupUi(this);

    QObject::connect(m_ui->pushButtonSearch, &QPushButton::clicked, this, &SearchWindow::searchClicked);
    
}

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

SearchWindow::~SearchWindow()
{}
