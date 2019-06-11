#include "GraphicView\ConnectorPainterPathCreator.h"
#include "GraphicView\Turtle.h"
#include <qmath.h>

using namespace GV;

ConnectorPainterPathCreator::ConnectorPainterPathCreator(ConnectorKind kind):m_kind(kind)
{}

QPainterPath ConnectorPainterPathCreator::getPath(QPointF begin, QPointF end) const
{
    QLineF line(begin, end);
    double angle = line.angle()*M_PI / 180.0;
    double length = line.length();

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
        case ConnectorKind::Bushing: {
            drawBushingPath(turtle, length);
            break;
        }
        case ConnectorKind::BeamForce: {
            drawBeamForcePath(turtle, length);
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

void ConnectorPainterPathCreator::drawBushingPath(Turtle & turtle, double length) const
{
    const double radius = 9.3;

    turtle.forward((length / 2));

    //drawing first circle

    turtle.save();

    turtle.rotate(M_PI / 2);
    const int nrOfSegments = 32;
    const double angle = 2 * M_PI / nrOfSegments;
    
    double segmentLength = radius*sqrt(2.0 - 2.0*cos(angle));
    
    for (int i = 0; i < nrOfSegments; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }    

    turtle.load();

    turtle.save();
    turtle.forward(2*radius/4, false);

    turtle.rotate(M_PI / 2);
    
    segmentLength = radius/2*sqrt(2.0 - 2.0*cos(angle));

    for (int i = 0; i < nrOfSegments; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }

    turtle.load();

    turtle.load();
    turtle.forward(2 * radius, false);
}

void ConnectorPainterPathCreator::drawBeamForcePath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);
    const double rectWidth1 = 5.1;
    const double rectHeight1 = 10.0;

    const double rectWidth2 = 10.0;
    const double rectHeight2 = 5.0;

    auto drawRect = [&turtle, this](const double rectWidth,const double rectHeight) {
        drawRectangle(turtle, rectWidth, rectHeight);
        turtle.rotate(-M_PI / 2);
        turtle.forward(rectWidth, false);
    };

    drawRect(rectWidth1,rectHeight1);
    drawRect(rectWidth2,rectHeight2);
    drawRect(rectWidth1,rectHeight1);
}
