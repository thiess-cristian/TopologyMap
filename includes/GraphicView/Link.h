#pragma once
#include "GraphicView\Element.h"

namespace GV
{
    class Link:public Element
    {
    public:
        Link(std::shared_ptr<GM::Element> elementModel);
    
    };
}