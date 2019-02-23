#pragma once

#include "SearchRequirements.h"
#include <qobject.h>
#include <memory>
class GraphicMechanism;
class GraphicElement;

class SearchManager :public QObject
{
    Q_OBJECT
public:
    SearchManager();
    void setGraphicMechanism(std::shared_ptr<GraphicMechanism> mechanism);


public slots:
    void search(const SearchRequirements& searchRequirements);

private:
    bool checkMatch(std::string input, const SearchRequirements& searchRequirements);
    void updateFoundElements();
    std::vector<GraphicElement*> m_foundElements;

    std::shared_ptr<GraphicMechanism> m_mechanism;

};