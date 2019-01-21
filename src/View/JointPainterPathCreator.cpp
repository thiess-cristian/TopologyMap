#include "JointPainterPathCreator.h"
#include "Turtle.h"
#include "qmath.h"


JointPainterPathCreator::JointPainterPathCreator(JointType type):m_type(type)
{}

QPainterPath JointPainterPathCreator::getPath(QPointF begin, QPointF end) const
{
    QLineF line(begin, end);
    double angleStart = line.angle()*M_PI / 180.0;
    double length = line.length();

    Turtle turtle(begin, -angleStart);

    
    
    switch (m_type) {
        case JointType::Revolute: {
            drawRevolutePath(turtle, length);
            break;
        }
        case JointType::Slider: {
            drawSliderPath(turtle, length);
            break;
        }
        case JointType::Cylindrical: {
            drawCylindricalPath(turtle, length);
            break;
        }
        case JointType::Screw: {

            break;
        }
        case JointType::Universal: {
            drawUniversalPath(turtle, length);
            break;
        }
        case JointType::Spherical: {
            drawSphericalPath(turtle, length);
            break;
        }
        case JointType::Planar: {

            break;
        }
        case JointType::Fixed: {

            break;
        }
        case JointType::ConstantVelocity: {

            break;
        }
        case JointType::Atpoint: {

            break;
        }
        case JointType::Inline: {
            drawInlinePath(turtle, length);
            break;
        }
        case JointType::Inplane: {

            break;
        }
        case JointType::Orientation: {

            break;
        }
        case JointType::Parallel: {

            break;
        }
        case JointType::Perpendicular: {

            break;
        }
        default:
            break;
    }
    
    auto path = turtle.getPath();
    path.lineTo(end);

    return path;
}

void JointPainterPathCreator::drawSphericalPath(Turtle & turtle, double length) const
{
    double radius = 7;

    turtle.forward((length / 2) - radius);
    turtle.rotate(M_PI / 2);

    int nrOfSegments = 32;
    double angle = 2 * M_PI / nrOfSegments;
    double segmentLength = angle*radius;

    for (int i = 0; i < nrOfSegments; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }

    turtle.rotate(-M_PI / 2);
    turtle.forward(2 * radius, false);
}

void JointPainterPathCreator::drawRevolutePath(Turtle & turtle, double length) const
{
    //drawing first circle
    const double radius = 5;

    turtle.forward((length / 2) - radius);
    turtle.rotate(M_PI / 2);

    const int nrOfSegments = 32;
    const double angle = 2 * M_PI / nrOfSegments;
    const double segmentLength = angle*radius;

    for (int i = 0; i < nrOfSegments; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }

    turtle.rotate(-M_PI / 2);
    turtle.forward(2 * radius, false);

    //drawing cilinder upper line
    const double cilinderLength=10;

    turtle.forward(cilinderLength, false);

    turtle.rotate(-M_PI / 2);
    turtle.forward(radius, false);

    turtle.rotate(-M_PI / 2);
    turtle.forward(cilinderLength + 2);
    turtle.rotate(M_PI);
    turtle.forward(cilinderLength + 2, false);

    for (int i = 0; i < nrOfSegments / 2; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(angle);
    }

    //drawing cilinder upper line
    turtle.forward(cilinderLength + 2);
    turtle.rotate(M_PI);
    turtle.forward(cilinderLength + 2, false);
    turtle.rotate(-M_PI);

    turtle.rotate(M_PI / 2);
    turtle.forward(radius, false);

    turtle.rotate(M_PI / 2);
    turtle.forward(radius, false);
}

void JointPainterPathCreator::drawCylindricalPath(Turtle & turtle, double length) const
{
    drawRevolutePath(turtle, length);

    const double cilinderLength = 10;
    const double radius = 5;
    turtle.rotate(M_PI);
    turtle.forward(cilinderLength+radius);
    turtle.rotate(M_PI);
    turtle.forward(cilinderLength+radius,false);
}

void JointPainterPathCreator::drawSliderPath(Turtle & turtle, double length) const
{
    double segment = 10;

    turtle.forward(length / 2);


    turtle.rotate(-M_PI / 2);
    turtle.forward(segment /2);

    turtle.rotate(M_PI / 2);
    turtle.forward(2 * segment);

    turtle.rotate(M_PI / 2);
    turtle.forward(segment);

    turtle.rotate(M_PI / 2);
    turtle.forward(2 * segment);

    turtle.rotate(M_PI / 2);
    turtle.forward(segment /2);

    turtle.rotate(M_PI / 2);
    turtle.forward(2*segment,false);
}

void JointPainterPathCreator::drawInlinePath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double triangleSide = 10;

    auto drawTriangle = [&turtle,&triangleSide]() {
        turtle.rotate(M_PI / 2);
        turtle.forward(triangleSide / 2);

        turtle.rotate(-2.0*M_PI / 3);
        turtle.forward(triangleSide);

        turtle.rotate(-2.0*M_PI / 3);
        turtle.forward(triangleSide);

        turtle.rotate(-2.0*M_PI / 3);
        turtle.forward(triangleSide / 2);
    };

    drawTriangle();

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3)/2.0*triangleSide, true);

    drawTriangle();

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3) / 2.0*triangleSide, false);

}

void JointPainterPathCreator::drawUniversalPath(Turtle & turtle, double length) const
{
    double radius = 10;

    turtle.forward((length / 2) - radius);

    turtle.rotate(-M_PI / 2);
    turtle.forward(radius,false);

    turtle.rotate(M_PI);
    turtle.forward(radius * 2);

    turtle.rotate(-M_PI / 2);

    int nrOfSegments = 32;
    double angle = 2 * M_PI / nrOfSegments;
    double segmentLength = angle*radius;

    for (int i = 0; i < nrOfSegments/2; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }

    turtle.rotate(-M_PI / 2);
    turtle.forward(radius,false);

    turtle.rotate(-M_PI / 2);
    turtle.forward(radius, false);

}
