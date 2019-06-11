#pragma once
#include "App\SearchManager.h"
#include <qwidget.h>
#include <memory>

class Ui_SearchWindow;

namespace App
{       
    class SearchWindow : public QWidget
    {
        Q_OBJECT
    public:
        explicit SearchWindow(std::shared_ptr<SearchManager> searchManager, QWidget *parent = 0);
        ~SearchWindow();

    protected slots:
        void searchClicked();
        void resetClicked();
        void selectColorClicked();

    signals:
        void sendSearchRequirements(const SearchRequirements& searchRequirements) const;
        void reset() const;
        void changeColor(const QColor& color) const;

    private:
        std::unique_ptr<Ui_SearchWindow> m_ui;
        std::shared_ptr<SearchManager> m_searchManager;
    };
}