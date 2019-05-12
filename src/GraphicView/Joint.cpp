#include "GraphicView\Joint.h"
#include "GraphicView\JointPainter.h"
#include <GraphicModel\Joint.h>

using namespace GV;

Joint::Joint(std::shared_ptr<GM::Element> elementModel):Link(elementModel)
{
    m_elementPainter = std::make_unique<JointPainter>(std::dynamic_pointer_cast<GM::Joint>(m_elementModel));
}
