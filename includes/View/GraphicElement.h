#pragma once
#include <qcolor.h>

class GraphicElement
{
public:
    GraphicElement();

    void setColor(const QColor& color);
protected:
    QColor m_color;
};