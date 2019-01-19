#include "ConnectorPainterPathCreator.h"
#include "Turtle.h"
#include <qmath.h>

ConnectorPainterPathCreator::ConnectorPainterPathCreator(ConnectorKind kind):m_kind(kind)
{}

QPainterPath ConnectorPainterPathCreator::getPath(QPointF begin, QPointF end) const
{
    QLineF line(begin, end);
    double angle = line.angle()*M_PI / 180.0;
    double length = line.length();

    Turtle turtle(begin,-angle);
    turtle.forward(length / 3, true);
    
    switch (m_kind) {
        case ConnectorKind::Spring: {
            drawSpringPath(turtle);
            break;
        }
        case ConnectorKind::Damper: {

            break;
        }
        default:
            break;
    }

    auto path = turtle.getPath();

    path.lineTo(end);

    return path;
}

void ConnectorPainterPathCreator::drawSpringPath(Turtle & turtle) const
{
    const int segment = 7;

    turtle.rotate(M_PI / 3);
    turtle.forward(segment, true);

    turtle.rotate(-2.0*M_PI / 3);
    turtle.forward(2 * segment, true);

    turtle.rotate(2.0*M_PI / 3);
    turtle.forward(2 * segment, true);

    turtle.rotate(-2.0*M_PI / 3);
    turtle.forward(2 * segment, true);

    turtle.rotate(2.0*M_PI / 3);
    turtle.forward(segment, true);
}


