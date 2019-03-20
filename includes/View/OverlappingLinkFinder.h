#pragma once

#include "GraphicMechanism.h"
#include <memory>
#include <map>

class GraphicLink;

class OverlappingLinkFinder
{
public:
    OverlappingLinkFinder(std::shared_ptr<GraphicMechanism> mechanism);

    void computeOverlappingCount();

private:
    void setOverlappingCount();

    std::shared_ptr<GraphicMechanism> m_graphicsMechanism;
    std::vector<GraphicLink*> m_links;

    std::vector<GraphicLink*> m_overlappingLinks;
};