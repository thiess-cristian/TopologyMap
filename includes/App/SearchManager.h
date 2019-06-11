#pragma once
#include <qobject.h>
#include <qcolor.h>
#include <memory>

namespace GM
{
    class Mechanism;
    class Element;
}

namespace App
{
    struct SearchRequirements
    {
        std::string searchText = "";
        bool motionBodyCheck = false;
        bool jointCheck = false;
        bool connectorCheck = false;
        bool matchCase = false;
        bool matchWhole = false;
        bool regEx = false;
    };

    class SearchManager :public QObject
    {
        Q_OBJECT
    public:
        SearchManager();
        void setMechanism(std::shared_ptr<GM::Mechanism> mechanism);
        QColor getHighlightColor()const;

    public slots:
        void search(const SearchRequirements& searchRequirements);
        void reset();
        void changeColor(const QColor& color);

    private:
        bool checkMatch(std::string input, const SearchRequirements& searchRequirements);
        void updateFoundElements();
        std::vector<std::shared_ptr<GM::Element>> m_foundElements;

        std::shared_ptr<GM::Mechanism> m_mechanism;

        QColor m_highlightColor;
    };


}