#pragma once

#include <qgraphicsscene.h>
#include <qobject.h>
#include <qpoint.h>
#include <memory>
#include <GraphicView\Element.h>

namespace GM
{
    class Mechanism;
}

namespace Perspective
{
    class IPerspective;
}
namespace Panel
{
    class InfoPanel;
}


namespace GV
{   
    class TopologyMapScene :public QGraphicsScene
    {
    public:
        TopologyMapScene(QWidget *parent = nullptr);
        void changePerspective(Perspective::IPerspective* perspective);
        void addElements(std::shared_ptr<GM::Mechanism> mechanism);
        void setInfoPanelRelations(std::shared_ptr<Panel::InfoPanel>);

        void setViewableHeight(size_t height);
        void setViewableWidth(size_t width);

        void resetColors();

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
        std::vector<Element*> m_elements;

        size_t m_viewableHeight;
        size_t m_viewableWidth;
        
    };
}