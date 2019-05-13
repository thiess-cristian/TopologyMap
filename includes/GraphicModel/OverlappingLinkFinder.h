#pragma once
#include <vector>
#include <memory>
#include <map>

namespace GM
{
    class Link;
    class Mechanism;

    class OverlappingLinkFinder
    {
    public:
        OverlappingLinkFinder(std::shared_ptr<Mechanism> mechanism);
        void computeOverlappingCount();

    private:
        void setOverlappingCount();

        std::shared_ptr<Mechanism> m_mechanism;
        std::vector<std::shared_ptr<Link>> m_links;
        std::vector<std::shared_ptr<Link>> m_overlappingLinks;
    };
}