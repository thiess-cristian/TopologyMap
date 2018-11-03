#pragma once
#include "Element.h"
#include <qpoint.h>

class MotionBody :public Element
{
public:
    MotionBody(const std::string& name);
    MotionBody();

    int getX() const;
    int getY() const;

private:
    QPoint m_coord;
};
