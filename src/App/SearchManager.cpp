#include "App\SearchManager.h"
#include "GraphicModel\Mechanism.h"
#include "GraphicModel\Element.h"
#include "DataModel\Mechanism.h"

#include <qregularexpression.h>

using namespace App;


SearchManager::SearchManager() :m_highlightColor(QColor(0, 255, 0))
{

}

void SearchManager::search(const SearchRequirements& searchRequirements)
{
    
    auto searchElements = [this, searchRequirements](auto container) {
        for (const auto& item : container) {
            std::string name = item.first;
            if (checkMatch(name, searchRequirements)) {
                m_foundElements.push_back(item.second);
            }
        }
    };


    if (searchRequirements.motionBodyCheck == true) {
        searchElements(m_mechanism->getElements()[DataModel::ElementType::MotionBody]);
    }

    if (searchRequirements.connectorCheck == true) {
        searchElements(m_mechanism->getElements()[DataModel::ElementType::Connector]);
    }

    if (searchRequirements.jointCheck == true) {
        searchElements(m_mechanism->getElements()[DataModel::ElementType::Joint]);
    }

    updateFoundElements();
}

void SearchManager::setMechanism(std::shared_ptr<GM::Mechanism> mechanism)
{
    m_mechanism = mechanism;
}

QColor SearchManager::getHighlightColor() const
{
    return m_highlightColor;
}

void SearchManager::reset()
{
    /*
    auto resetColor = [this](auto elements) {
        for (auto& item : elements) {
            item.second->resetColor();
        }
    };

    resetColor(m_mechanism->getElements()[DataModel::ElementType::MotionBody]);
    resetColor(m_mechanism->getElements()[DataModel::ElementType::Joint]);
    resetColor(m_mechanism->getElements()[DataModel::ElementType::MotionBody]);
    */
    for (auto& container : m_mechanism->getElements()) {
        for (auto& element : container.second) {
            element.second->setColor(element.second->DefaultColor);
        }
    }
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
   
    m_foundElements.clear();
}