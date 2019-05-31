#pragma once
#include "App\CompareManager.h"
#include <qwidget.h>
#include <memory>

class Ui_CompareWindow;
class QTabWidget;

namespace App
{
    class TopologyMapTab;

    class CompareWindow : public QWidget
    {
        Q_OBJECT
    public:
        CompareWindow(QTabWidget* tabWidget);
        void setTabs(const std::vector<std::shared_ptr<TopologyMapTab>> tabs);
        void initComboBoxes();

    protected slots:
        void compare();

    private:

        std::unique_ptr<Ui_CompareWindow> m_ui;        
        std::vector<std::shared_ptr<TopologyMapTab>> m_tabs;

        CompareManager m_compareManager;

        QTabWidget* m_tabWidget;
    };
}