#pragma once
#include <QMainWindow>
#include <memory>
#include "TopologyMap.h"

class Ui_TopologyMapWindow;


class QLabel;

namespace Panel
{
    class InfoPanel;
    class LegendPanel;
}

namespace GV
{
    class TopologyMapScene;
}

namespace App
{
    class SceneZoom;
    class SearchWindow;
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

    private:
        std::unique_ptr<Ui_TopologyMapWindow> m_ui;
        std::unique_ptr<SearchWindow> m_searchWindow;

        QString m_filename;
        QLabel* m_label;

        std::vector<TopologyMapTab*> m_tabs;
        
        TopologyMap m_topologyMap;
        std::shared_ptr<SearchManager> m_searchManager;
    };


}