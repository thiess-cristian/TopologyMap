#pragma once
#include "GraphicModel\Link.h"

namespace GM
{
    class Joint :public Link
    {
    public:
        Joint(std::shared_ptr<DataModel::Element> linkDataModel,
             std::shared_ptr<Element> actionGraphicModel,
             std::shared_ptr<Element> baseGraphicModel);
    };
}