#pragma once
#include <qpoint.h>
#include <qpainterpath.h>

class Turtle
{
public:
    Turtle(double x, double y, double dir);
    Turtle(QPointF start, double dir);
    void rotate(double angle);
    void forward(double length, bool draw = true);
    QPainterPath getPath()const;

private:
    QPainterPath m_path;
    double m_x;
    double m_y;
    double m_dir;
};