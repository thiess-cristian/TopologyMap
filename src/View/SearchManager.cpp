#include "SearchManager.h"
#include "GraphicMechanism.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"

#include <qregularexpression.h>
#include <algorithm>
#include <string> 

SearchManager::SearchManager() :m_highlightColor(QColor(0, 255, 0))
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

void SearchManager::reset()
{
    QColor motionBodyColor(128, 128, 255, 128);
    QColor connectorColor(Qt::red);
    QColor jointColor(Qt::black);

    auto resetColor = [this](auto elements,QColor color) {
        for (auto& item : elements) {
            item.second->setColor(color);
        }
    };

    resetColor(m_mechanism->getGraphicMotionBodies(), motionBodyColor);
    resetColor(m_mechanism->getGraphicJoints(), jointColor);
    resetColor(m_mechanism->getGraphicConnectors(), connectorColor);
}

void SearchManager::changeColor(const QColor & color)
{
    m_highlightColor = color;
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
    for (const auto& motionBody : m_foundElements) {
        motionBody->setColor(m_highlightColor);
    }
}
