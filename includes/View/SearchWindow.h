#pragma once

#include "SearchRequirements.h"
#include <qwidget.h>
#include <memory>

class Ui_SearchWindow;

class SearchWindow: public QWidget
{
    Q_OBJECT
public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

protected slots:
    void searchClicked();

signals:
    void sendSearchRequirements(const SearchRequirements& searchRequirements) const;

private:
    std::unique_ptr<Ui_SearchWindow> m_ui;
};