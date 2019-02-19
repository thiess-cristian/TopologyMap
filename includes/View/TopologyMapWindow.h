#pragma once

#include <QMainWindow>
#include <memory>
#include "ElementsManager.h"

class Ui_TopologyMapWindow;
class TopologyMapScene;
class Zoom;

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
private:
    std::unique_ptr<Ui_TopologyMapWindow> m_ui;

    QString m_filename;

    TopologyMapScene* m_scene;
    ElementsManager m_manager;
    std::unique_ptr<Zoom> m_zoom;
};
