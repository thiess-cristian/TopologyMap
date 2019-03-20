#include "OverlappingLinkFinder.h"
#include "GraphicConnector.h"
#include "GraphicJoint.h"
#include <iostream>

OverlappingLinkFinder::OverlappingLinkFinder(std::shared_ptr<GraphicMechanism> mechanism) :m_graphicsMechanism(mechanism)
{
    for (const auto& conector : m_graphicsMechanism->getGraphicConnectors()) {
        m_links.push_back(conector.second);
    }

    for (const auto& joint : m_graphicsMechanism->getGraphicJoints()) {
        m_links.push_back(joint.second);
    }
}

void OverlappingLinkFinder::computeOverlappingCount()
{
    bool firstWasInserted = false;

    auto insert = [&](int i,int& j) {
        m_overlappingLinks.push_back(m_links[j]);
        m_links.erase(m_links.begin() + j);
        j--;
        if (!firstWasInserted) {
            firstWasInserted = true;
            m_overlappingLinks.push_back(m_links[i]);
        }
    };

    for (int i = 0; i < m_links.size() - 1; i++) {
        m_overlappingLinks.clear();
        firstWasInserted = false;

        for (int j = i + 1; j < m_links.size(); j++) {
            
            if (m_links[i]->overlaps(*m_links[j])) {
                insert(i, j);
            } else if (m_links[i]->reverseOverlaps(*m_links[j])) {
                insert(i, j);
                m_links[i]->setReverseOverlaps(true);                
            }
        }

        if (firstWasInserted) {
            setOverlappingCount();
        }
    }
}

void OverlappingLinkFinder::setOverlappingCount()
{
    int count = 1;
    for (auto& link : m_overlappingLinks) {
        link->setOverlappingCount(count++);
    }
}
