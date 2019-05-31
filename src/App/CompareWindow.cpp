#include "App\CompareWindow.h"
#include "App\TopologyMapTab.h"
#include "App\TopologyMapView.h"
#include "ui_CompareWindow.h"
#include <qtabwidget.h>

using namespace App;

CompareWindow::CompareWindow(QTabWidget* tabWidget):m_tabWidget(tabWidget)
{    
    m_ui = std::make_unique<Ui_CompareWindow>();
    m_ui->setupUi(this);

    QObject::connect(m_ui->pushButtonCompare, &QPushButton::released, this, &CompareWindow::compare);
}

void CompareWindow::setTabs(const std::vector<std::shared_ptr<TopologyMapTab>> tabs)
{
    m_tabs = tabs;
}

void CompareWindow::initComboBoxes()
{
    m_ui->comboBoxModel1->clear();
    m_ui->comboBoxModel2->clear();
    for (auto tab : m_tabs) {
        m_ui->comboBoxModel1->addItem(tab->getName().c_str());
        m_ui->comboBoxModel2->addItem(tab->getName().c_str());
    }

}

void CompareWindow::compare()
{
    auto model1Index = m_ui->comboBoxModel1->currentIndex();
    auto model2Index = m_ui->comboBoxModel2->currentIndex();
    m_compareManager.compare(m_tabs[model1Index], m_tabs[model2Index]);
    close();
}
