#include "App\SearchWindow.h"
#include "ui_SearchWindow.h"
#include <qcolordialog.h>

using namespace App;

SearchWindow::SearchWindow(std::shared_ptr<SearchManager> searchManager, QWidget * parent) :m_searchManager(searchManager), QWidget(parent)
{
    m_ui = std::make_unique<Ui_SearchWindow>();
    m_ui->setupUi(this);

    QObject::connect(this, &SearchWindow::sendSearchRequirements, m_searchManager.get(), &SearchManager::search);
    QObject::connect(this, &SearchWindow::reset, m_searchManager.get(), &SearchManager::reset);
    QObject::connect(this, &SearchWindow::changeColor, m_searchManager.get(), &SearchManager::changeColor);

    QObject::connect(m_ui->pushButtonSearch, &QPushButton::clicked, this, &SearchWindow::searchClicked);
    QObject::connect(m_ui->pushButtonSelectColor, &QPushButton::clicked, this, &SearchWindow::selectColorClicked);
    

    QImage image(20, 20, QImage::Format_ARGB32);

    image.fill(m_searchManager->getHighlightColor());

    QPixmap pixmap(QPixmap::fromImage(image));
    m_ui->labelColor->setPixmap(pixmap);
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
    QColor color = QColorDialog::getColor(m_searchManager->getHighlightColor(), this, "select color");

    QImage image(20, 20, QImage::Format_ARGB32);

    image.fill(color);

    QPixmap pixmap(QPixmap::fromImage(image));
    m_ui->labelColor->setPixmap(pixmap);

    emit changeColor(color);
}