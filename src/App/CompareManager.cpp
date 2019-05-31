#include "App\CompareManager.h"
#include "App\TopologyMapTab.h"
#include "App\TopologyMapView.h"

#include "GraphicModel\Mechanism.h"
#include "GraphicModel\Element.h"

#include "DataModel\Element.h"

using namespace App;

CompareManager::CompareManager()
{

}

void CompareManager::compare(std::shared_ptr<TopologyMapTab> model1, std::shared_ptr<TopologyMapTab> model2) const
{
    auto model1DataModel = model1->getTopologyMap().getDataModel();
    auto model2DataModel = model2->getTopologyMap().getDataModel();

    auto model1GraphicModel = model1->getTopologyMap().getGraphicModel();
    
    for (auto container : model1DataModel->getElements()) {
        for (auto item : container.second) {

            auto model2ElementContainer = model2DataModel->getElements()[container.first];
            auto graphicItem = model1GraphicModel->getElements()[container.first][item.first];

            if (itemIsNotInModel(item.second, model2ElementContainer)) {
                graphicItem->setColor(Qt::red);
            } else if(itemIsDifferent(item.second, model2ElementContainer)){
                graphicItem->setColor(Qt::yellow);
            }
        }
    }
}

bool App::CompareManager::itemIsNotInModel(std::shared_ptr<DataModel::Element> element, std::map<std::string, std::shared_ptr<DataModel::Element>> elementContainer) const
{    
    return elementContainer.count(element->getName()) == 0;
}

bool App::CompareManager::itemIsDifferent(std::shared_ptr<DataModel::Element> element, std::map<std::string, std::shared_ptr<DataModel::Element>> elementContainer) const
{
    auto comparedElement = elementContainer[element->getName()];
    return (*comparedElement)!=(*element);
}

