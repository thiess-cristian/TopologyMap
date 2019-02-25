#pragma once

#include <QMainWindow>
#include <memory>
#include "ElementsManager.h"
#include "SearchManager.h"

class Ui_TopologyMapWindow;
class TopologyMapScene;
class Zoom;
class Legend;
class SearchWindow;
class QLabel;

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
    void openSearchWindow();

private:
    std::unique_ptr<Ui_TopologyMapWindow> m_ui;
    std::unique_ptr<SearchWindow> m_searchWindow;

    QString m_filename;

    QLabel* m_label;

    TopologyMapScene* m_scene;
    ElementsManager m_manager;
    std::shared_ptr<SearchManager> m_searchManager;
    std::unique_ptr<Zoom> m_zoom;
    std::unique_ptr<Legend> m_legend;
};
