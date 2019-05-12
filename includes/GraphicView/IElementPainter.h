#pragma once

class QPainter;

namespace GV
{
    class IElementPainter
    {
    public:
        ~IElementPainter() = default;
        virtual void paintItem(QPainter * painter) const =0;
    };
}
