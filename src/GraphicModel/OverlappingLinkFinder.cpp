#include "GraphicModel\OverlappingLinkFinder.h"
#include "GraphicModel\Mechanism.h"
#include "GraphicModel\Link.h"

using namespace GM;

OverlappingLinkFinder::OverlappingLinkFinder(std::shared_ptr<Mechanism> mechanism) :m_mechanism(mechanism)
{
    auto elements = m_mechanism->getElements();

    for (auto conector :elements [DataModel::ElementType::Connector]) {
        auto link = std::dynamic_pointer_cast<GM::Link>(conector.second);
        m_links.push_back(link);
    }

    for (auto joint : elements[DataModel::ElementType::Joint]) {
        auto link = std::dynamic_pointer_cast<GM::Link>(joint.second);
        m_links.push_back(link);
    }
}

void OverlappingLinkFinder::computeOverlappingCount()
{
    bool firstWasInserted = false;

    for (int i = 0; i < m_links.size() - 1; i++) {
        m_overlappingLinks.clear();        
        m_overlappingLinks.push_back(m_links[i]);
        
        for (int j = i + 1; j < m_links.size(); j++) {

            if (m_links[i]->overlaps(*m_links[j])) {
                m_links[j]->setReverseOverlaps(m_links[i]->reverseOverlaps(*m_links[j]));
                m_overlappingLinks.push_back(m_links[j]);
                m_links.erase(m_links.begin() + j);
                j--;
            }                          
        }        
        setOverlappingCount();        
    }
}

void OverlappingLinkFinder::setOverlappingCount()
{
    int count = 0;
    for (auto& link : m_overlappingLinks) {
        link->setOverlappingCount(count++);
    }
}
