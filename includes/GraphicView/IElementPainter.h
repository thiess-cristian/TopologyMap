#pragma once

class QPainter;

namespace GV
{
    class IElementPainter
    {
    public:
        virtual void paintItem(QPainter * painter) const =0;
    };
}
