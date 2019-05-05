#pragma once
#include <qpoint.h>
#include <qpainterpath.h>


namespace GV
{
    class Turtle
    {
    public:
        Turtle(double x, double y, double dir);
        Turtle(QPointF start, double dir);
        void rotate(double angle);
        void forward(double length, bool draw = true);

        void save();
        void load();

        QPainterPath getPath()const;

    private:
        QPainterPath m_path;

        struct State
        {
            State(double x, double y, double dir) :m_x(x), m_y(y), m_dir(dir)
            {}

            State()
            {}
            double m_x = 0.0;
            double m_y = 0.0;
            double m_dir = 0.0;
        };

        State m_current;
        State m_saved;
    };
}