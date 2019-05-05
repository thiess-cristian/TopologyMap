#pragma once
#include "GraphicView\IElementPainter.h"
#include <memory>

namespace GM
{
    class Joint;
}

namespace GV
{
    class JointPainter :public IElementPainter
    {
    public:    
        JointPainter(std::shared_ptr<GM::Joint> jointModel);
        // Inherited via IElementPainter
        virtual void paintItem(QPainter * painter) const override;
    private:
        std::shared_ptr<GM::Joint> m_jointModel;
    };
}