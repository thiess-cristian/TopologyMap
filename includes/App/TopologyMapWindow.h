#pragma once
#include <QMainWindow>
#include <memory>
#include "TopologyMap.h"

class Ui_TopologyMapWindow;
class QLabel;

namespace App
{
    class SearchWindow;
    class CompareWindow;
    class SearchManager;
    class TopologyMapTab;

    class TopologyMapWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit TopologyMapWindow(QWidget *parent = 0);
        ~TopologyMapWindow();

        protected slots:
        void openFile();
        void saveAsFile();
        void saveFile();
        void loadSceneFromFile();
        void changePerspectiveToTop();
        void changePerspectiveToSide();
        void changePerspectiveToFront();
        void changePerspectiveCircle();
        void changePerspectiveForceDirected();

        void displayLegend(bool checked);
        void displayInfoPanel(bool checked);
        void openSearchWindow();

        void displayMotionBodyName(bool checked);
        void displayJointName(bool checked);
        void displayConnectorName(bool checked);

        void closeTab(int index);

        void compareModels();
        void resetColors();
    private:
        std::unique_ptr<Ui_TopologyMapWindow> m_ui;
        std::unique_ptr<SearchWindow> m_searchWindow;
        std::unique_ptr<CompareWindow> m_compareWindow;

        QString m_filename;
        QLabel* m_label;

        std::vector<std::shared_ptr<TopologyMapTab>> m_tabs;                
        std::shared_ptr<SearchManager> m_searchManager;
    };
}