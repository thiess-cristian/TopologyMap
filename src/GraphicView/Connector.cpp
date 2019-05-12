#include "GraphicView\Connector.h"
#include "GraphicView\ConnectorPainter.h"
#include <GraphicModel\Connector.h>

using namespace GV;

Connector::Connector(std::shared_ptr<GM::Element> elementModel):Link(elementModel)
{
    m_elementPainter = std::make_unique<ConnectorPainter>(std::dynamic_pointer_cast<GM::Connector>(m_elementModel));
}
