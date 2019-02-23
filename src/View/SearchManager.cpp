#include "SearchManager.h"
#include "GraphicMechanism.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

#include <qregularexpression.h>
#include <algorithm>
#include <string> 

SearchManager::SearchManager()
{

}

void SearchManager::search(const SearchRequirements& searchRequirements)
{
    auto searchElements = [this,searchRequirements](auto container) {
        for (const auto& item : container) {
            std::string name = item.first;
            if (checkMatch(name, searchRequirements)) {
                m_foundElements.push_back(item.second);
            }
        }
    };


    if (searchRequirements.motionBodyCheck == true) {
        searchElements(m_mechanism->getGraphicMotionBodies());
    }

    if (searchRequirements.connectorCheck == true) {
        searchElements(m_mechanism->getGraphicConnectors());
    }

    if (searchRequirements.jointCheck == true) {
        searchElements(m_mechanism->getGraphicJoints());
    }

    updateFoundElements();
}

void SearchManager::setGraphicMechanism(std::shared_ptr<GraphicMechanism> mechanism)
{
    m_mechanism = mechanism;
}

bool SearchManager::checkMatch(std::string name, const SearchRequirements & searchRequirements)
{
    bool result = false;
    if (searchRequirements.regEx) {
        QRegularExpression regEx(searchRequirements.searchText.c_str());

        QRegularExpressionMatch match = regEx.match(name.c_str());

        result = match.hasMatch();

    } else {
        //make string lowercase if its not match case
        if (!searchRequirements.matchCase) {
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        }

        //if the match whole is set just check if the names are equal
        if (searchRequirements.matchWhole) {            
            result = name == searchRequirements.searchText;
        } else {
            //else check if the search text is a substring
            result = name.find(searchRequirements.searchText) != std::string::npos;
        }
    }
    return result;
}

void SearchManager::updateFoundElements()
{
    QColor green(0, 255, 0);
    for (const auto& motionBody : m_foundElements) {
        motionBody->setColor(green);
    }
}
