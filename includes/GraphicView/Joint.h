#pragma once
#include "GraphicView\Link.h"

namespace GV
{
    class Joint :public Link
    {
    public:
        Joint(std::shared_ptr<GM::Element> elementModel);

    };
}