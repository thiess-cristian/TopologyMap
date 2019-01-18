#include "Turtle.h"

Turtle::Turtle(double x, double y, double dir):Turtle(QPointF(x,y),dir)
{
   
}

Turtle::Turtle(QPointF start, double dir):m_x(start.x()),m_y(start.y()),m_dir(dir)
{
    m_path.moveTo(m_x,m_y);
}

void Turtle::rotate(double angle)
{
    m_dir += angle;
}

void Turtle::forward(double length, bool draw)
{
    double dx = m_x + length * cos(m_dir);
    double dy = m_y + length * sin(m_dir);

    if (draw) {
        m_path.lineTo(dx, dy);
    } else {
        m_path.moveTo(dx, dy);
    }
    m_x = dx;
    m_y = dy;
}

QPainterPath Turtle::getPath() const
{
    return m_path;
}
