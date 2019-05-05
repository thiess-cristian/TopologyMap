#pragma once
#include "GraphicView\IElementPainter.h"
#include <memory>
namespace GM
{
    class MotionBody;
}

namespace GV
{
    class MotionBodyPainter:public IElementPainter
    {
    public:
        MotionBodyPainter(std::shared_ptr<GM::MotionBody> motionBodyModel);
        // Inherited via IElementPainter
        virtual void paintItem(QPainter * painter) const override;
    private:
        std::shared_ptr<GM::MotionBody> m_motionBodyModel;
    };
}