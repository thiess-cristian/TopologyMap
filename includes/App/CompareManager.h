#pragma once
#include <memory>
#include <map>
#include <string>

namespace DataModel
{
    class Element;
}

namespace App
{   
    class TopologyMapTab;

    class CompareManager
    {
    public:
        CompareManager();
        void compare(std::shared_ptr<TopologyMapTab> model1, std::shared_ptr<TopologyMapTab> model2) const;
        bool itemIsNotInModel(std::shared_ptr<DataModel::Element> element, std::map<std::string, std::shared_ptr<DataModel::Element>> elementContainer) const;
        bool itemIsDifferent(std::shared_ptr<DataModel::Element> element, std::map<std::string, std::shared_ptr<DataModel::Element>> elementContainer) const;

    };
}