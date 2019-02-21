#include "Turtle.h"

Turtle::Turtle(double x, double y, double dir):Turtle(QPointF(x,y),dir)
{
   
}

Turtle::Turtle(QPointF start, double dir):m_current(start.x(),start.y(),dir)
{
    m_path.moveTo(m_current.m_x,m_current.m_y);
}

void Turtle::rotate(double angle)
{
    m_current.m_dir += angle;
}

void Turtle::forward(double length, bool draw)
{
    m_current.m_x += length * cos(m_current.m_dir);
    m_current.m_y += length * sin(m_current.m_dir);

    if (draw) {
        m_path.lineTo(m_current.m_x, m_current.m_y);
    } else {
        m_path.moveTo(m_current.m_x, m_current.m_y);
    }
}

void Turtle::save()
{
    m_saved = m_current;
}

void Turtle::load()
{
    m_current = m_saved;
    m_path.moveTo(m_current.m_x, m_current.m_y);
}

QPainterPath Turtle::getPath() const
{
    return m_path;
}
