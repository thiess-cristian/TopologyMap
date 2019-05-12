#include "GraphicModel\Connector.h"
#include "GraphicModel\Bounder.h"

using namespace GM;

Connector::Connector(std::shared_ptr<DataModel::Element> linkDataModel,
             std::shared_ptr<Element> actionGraphicModel,
             std::shared_ptr<Element> baseGraphicModel) :
    Link(linkDataModel, actionGraphicModel, baseGraphicModel)
{
    DefaultColor = QColor(Qt::red);    
}
