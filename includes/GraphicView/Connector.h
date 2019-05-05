#pragma once
#include "GraphicView\Link.h"

namespace GV
{
    class Connector:public Link
    {
    public:
        Connector(std::shared_ptr<GM::Element> elementModel);

    };
}