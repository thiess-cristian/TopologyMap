#pragma once

#include <qgraphicsscene.h>
#include <qobject.h>
#include <memory>

namespace GM
{
    class Mechanism;
}

namespace GV
{
    class TopologyMapScene :public QGraphicsScene
    {
    public:
        TopologyMapScene(std::shared_ptr<GM::Mechanism> mechanism);
    };
}