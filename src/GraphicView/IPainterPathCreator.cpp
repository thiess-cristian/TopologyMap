#include "IPainterPathCreator.h"
#include "GraphicView\Turtle.h"
#include "qmath.h"

using namespace GV;


void IPainterPathCreator::drawTriangle(Turtle & turtle, double triangleSide) const
{
    turtle.rotate(M_PI / 2);
    turtle.forward(triangleSide / 2);

    turtle.rotate(-2.0*M_PI / 3);
    turtle.forward(triangleSide);

    turtle.rotate(-2.0*M_PI / 3);
    turtle.forward(triangleSide);

    turtle.rotate(-2.0*M_PI / 3);
    turtle.forward(triangleSide / 2);
}

void IPainterPathCreator::drawCircle(Turtle & turtle, double radius) const
{
    int nrOfSegments = 32;
    double angle = 2 * M_PI / nrOfSegments;
    double segmentLength = angle*radius;

    for (int i = 0; i < nrOfSegments; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }

}

void IPainterPathCreator::drawHalfCircle(Turtle & turtle, double radius) const
{
    int nrOfSegments = 32;
    double angle = 2 * M_PI / nrOfSegments;
    double segmentLength = angle*radius;

    for (int i = 0; i < nrOfSegments / 2; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }
}

void IPainterPathCreator::drawRectangle(Turtle& turtle, double width, double height) const
{
    turtle.rotate(M_PI / 2);
    turtle.forward(height / 2);

    turtle.rotate(-M_PI / 2);
    turtle.forward(width);

    turtle.rotate(-M_PI / 2);
    turtle.forward(height);

    turtle.rotate(-M_PI / 2);
    turtle.forward(width);

    turtle.rotate(-M_PI / 2);
    turtle.forward(height / 2);
}

