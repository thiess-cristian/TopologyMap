#pragma once

#include <qgraphicsscene.h>
#include <qobject.h>
#include <qpoint.h>
#include <memory>

namespace GM
{
    class Mechanism;
}

namespace Perspective
{
    class IPerspective;
}


namespace GV
{   
    class TopologyMapScene :public QGraphicsScene
    {
    public:
        TopologyMapScene(std::shared_ptr<GM::Mechanism> mechanism);
        void changePerspective(Perspective::IPerspective* perspective);

    public slots:
        void applyScale(double scaleFactor);
        void applyTranslation(QPointF translatePoint);

    private:
        double computeScaleFactor();
        QPointF computeTranslationPoint();

        void changeMotionBodiesPerspective(Perspective::IPerspective* perspective);
        void changeJointsPerspective(Perspective::IPerspective* perspective);
        void changeConnectorsPerspective(Perspective::IPerspective* perspective);

        void setStackingOrder();

        std::shared_ptr<GM::Mechanism> m_mechanism;
        
    };
}