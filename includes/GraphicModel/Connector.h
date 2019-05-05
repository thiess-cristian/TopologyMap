#pragma once
#include "GraphicModel\Link.h"

namespace GM
{
    class Connector :public Link
    {
    public:
        Connector(std::shared_ptr<DataModel::Element> linkDataModel,
              std::shared_ptr<Element> actionGraphicModel,
              std::shared_ptr<Element> baseGraphicModel);
    };


}