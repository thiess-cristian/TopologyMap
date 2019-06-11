#include "GraphicView\JointPainterPathCreator.h"
#include "GraphicView\Turtle.h"
#include "qmath.h"

using namespace GV;

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
            drawScrewPath(turtle, length);
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
            drawPlanarPath(turtle, length);
            break;
        }
        case JointType::Fixed: {
            drawFixedPath(turtle, length);
            break;
        }
        case JointType::ConstantVelocity: {
            drawConstantVelocityPath(turtle, length);
            break;
        }
        case JointType::Atpoint: {
            drawAtpointPath(turtle, length);
            break;
        }
        case JointType::Inline: {
            drawInlinePath(turtle, length);
            break;
        }
        case JointType::Inplane: {
            drawInplanePath(turtle, length);
            break;
        }
        case JointType::Orientation: {
            drawOrientationPath(turtle, length);
            break;
        }
        case JointType::Parallel: {
            drawParallelPath(turtle, length);
            break;
        }
        case JointType::Perpendicular: {
            drawPerpendicularPath(turtle, length);
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

    turtle.forward((length / 2));
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
    const double radius = 5;

    turtle.forward((length / 2) - radius);

    //drawing first circle

    turtle.save();

    turtle.rotate(M_PI / 2);
    const int nrOfSegments = 32;
    const double angle = 2 * M_PI / nrOfSegments;
    //const double segmentLength = angle*radius;
    const double segmentLength = radius*sqrt(2.0 - 2.0*cos(angle));

    //turtle.rotate(-angle / 2);
    for (int i = 0; i < nrOfSegments; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(-angle);
    }

    //turtle.rotate(-M_PI / 2);

    turtle.load();
    turtle.forward(2 * radius, false);

    //drawing cilinder upper line
    const double cilinderLength=10;

    turtle.forward(cilinderLength, false);

    turtle.rotate(-M_PI / 2);
    turtle.forward(radius, false);

    turtle.rotate(-M_PI / 2);
    turtle.forward(cilinderLength + 3);
    turtle.rotate(M_PI);
    turtle.forward(cilinderLength + 3, false);

    turtle.save();
    //turtle.rotate(angle / 2);
    for (int i = 0; i < nrOfSegments / 2; i++) {
        turtle.forward(segmentLength);
        turtle.rotate(angle);
    }

    turtle.load();
    turtle.rotate(M_PI / 2);
    turtle.forward(radius*2.0,false);
    turtle.rotate(M_PI / 2);

    //drawing cilinder lower line
    turtle.forward(cilinderLength + 3);
    turtle.rotate(M_PI);
    turtle.forward(cilinderLength + 3, false);
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

    turtle.forward((length / 2));

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

void JointPainterPathCreator::drawAtpointPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double triangleSide = 10;

    drawTriangle(turtle,triangleSide);

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3) / 2.0*triangleSide, false);

    drawTriangle(turtle, triangleSide);

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3) / 2.0*triangleSide, false);
}

void JointPainterPathCreator::drawConstantVelocityPath(Turtle & turtle, double length) const
{
    double radius = 7;

    turtle.forward((length / 2)-radius);
    turtle.rotate(M_PI / 2);

    drawCircle(turtle, radius);

    turtle.rotate(-M_PI / 2);
    turtle.forward(radius, false);

    const double triangleSide = 9;

    drawTriangle(turtle, triangleSide);

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3) / 2.0*triangleSide, false);

    drawTriangle(turtle, triangleSide);

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3) / 2.0*triangleSide, false);
}

void JointPainterPathCreator::drawFixedPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    double side = 6;

    auto DShape = [&turtle,&side,this]() {
        turtle.rotate(M_PI / 2);
        turtle.forward(side);

        turtle.rotate(-M_PI / 2);
        turtle.forward(side);

        drawHalfCircle(turtle, side);

        turtle.forward(side + 1);
        turtle.rotate(-M_PI / 2);

        turtle.forward(side);
    };

    auto reverseDShape = [&turtle, &side, this]() {
        turtle.rotate(-M_PI / 2);
        turtle.forward(side);

        turtle.rotate(-M_PI / 2);
        turtle.forward(side);

        drawHalfCircle(turtle, side);

        turtle.forward(side+2);
        turtle.rotate(-M_PI / 2);

        turtle.forward(side);
    };

    DShape();

    turtle.rotate(-M_PI/2);
    turtle.forward(side*3.5,false);

    reverseDShape();
}

void JointPainterPathCreator::drawInplanePath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double rectWidth = 8;
    const double rectHeight = 10;

    drawRectangle(turtle, rectWidth, rectHeight);

    turtle.rotate(-M_PI / 2);
    turtle.forward(rectWidth, false);

    drawAtpointPath(turtle, 5);
}

void JointPainterPathCreator::drawOrientationPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double triangleSide = 10;

    drawTriangle(turtle,triangleSide);

    turtle.rotate(-M_PI / 2);
    turtle.forward(sqrt(3) / 2.0*triangleSide, false);
}

void JointPainterPathCreator::drawParallelPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double rectWidth = 4;
    const double rectHeight = 10;

    auto drawParallel = [&rectWidth,&rectHeight,&turtle,this]() {
        drawRectangle(turtle, rectWidth, rectHeight);
        turtle.rotate(-M_PI / 2);
        turtle.forward(rectWidth, false);
    };

    drawParallel();
    
    turtle.forward(4, false);

    drawParallel();

    drawAtpointPath(turtle, 4);
}

void JointPainterPathCreator::drawPerpendicularPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double firstRectWidth = 4;
    const double firstRectHeight = 10;

    const double secondRectWidth = 7;
    const double secondRectHeight = 4;

    drawRectangle(turtle, firstRectWidth, firstRectHeight);

    turtle.rotate(-M_PI / 2);
    turtle.forward(firstRectWidth, false);

    drawRectangle(turtle, secondRectWidth, secondRectHeight);

    turtle.rotate(-M_PI / 2);
    turtle.forward(secondRectWidth, false);

    drawAtpointPath(turtle, 4);
}

void JointPainterPathCreator::drawPlanarPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);

    const double outerRectWidth = 20;
    const double outerRectHeight = 10;

    const double innerRectWidth = outerRectWidth/3;
    const double innerRectHeight = outerRectHeight/3;

    drawRectangle(turtle, outerRectWidth, outerRectHeight);

    turtle.rotate(-M_PI / 2);
    turtle.forward(outerRectWidth/3, false);

    drawRectangle(turtle, innerRectWidth, innerRectHeight);

    turtle.rotate(-M_PI / 2);
    turtle.forward(2 * outerRectWidth / 3, false);
}

void JointPainterPathCreator::drawScrewPath(Turtle & turtle, double length) const
{
    turtle.forward(length / 2);
    const double rectWidth = 4.7;
    const double rectHeight = 10.0;

    auto drawRect = [&rectWidth, &rectHeight, &turtle, this]() {
        drawRectangle(turtle, rectWidth, rectHeight);
        turtle.rotate(-M_PI / 2);
        turtle.forward(rectWidth, false);
    };

    for (int i = 0; i < 4; i++) {
        drawRect();
    }
}
