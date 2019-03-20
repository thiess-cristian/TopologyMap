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

    //QPainterPath path(begin);
    //path.quadTo(end,begin+QPointF(20,20));

    //Turtle turtle(path.currentPosition(), -angle);
    Turtle turtle(begin,-angle);
    
    switch (m_kind) {
        case ConnectorKind::Spring: {
            drawSpringPath(turtle,length);
            break;
        }
        case ConnectorKind::Damper: {
            drawDamperPath(turtle, length);
            break;
        }
        default:
            break;
    }
    
    auto path = turtle.getPath();

    path.lineTo(end);

    return path;
}

void ConnectorPainterPathCreator::drawSpringPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 4);

    const int segment = 5;

    const int nrOfPeaks = length / 2 / segment / 2;

    for (int i = 0; i < nrOfPeaks; i++) {
        turtle.rotate(M_PI / 3);
        turtle.forward(segment);

        turtle.rotate(-2.0*M_PI / 3);
        turtle.forward(2 * segment);

        turtle.rotate(2.0*M_PI / 3);
        turtle.forward(segment);

        turtle.rotate(-M_PI / 3);
    }
}

void ConnectorPainterPathCreator::drawDamperPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const int segment = 8;

    turtle.rotate(-M_PI / 2);
    turtle.forward(segment / 2);
   
    turtle.forward(segment / 2, false);

    turtle.rotate(M_PI / 2);
    turtle.forward(segment);

    turtle.rotate(M_PI / 2);
    turtle.forward(segment*2);

    turtle.rotate(M_PI / 2);
    turtle.forward(segment);

    turtle.rotate(M_PI / 2);

    turtle.forward(segment / 2, false);
    turtle.forward(segment/2);

    turtle.rotate(M_PI / 2);
    turtle.forward(segment,false);
}

