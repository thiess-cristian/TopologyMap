#pragma once
#include "GraphicView\IPainterPathCreator.h"
#include "XMLTagNames.h"

namespace GV
{
    class Turtle;

    class JointPainterPathCreator :public IPainterPathCreator
    {
    public:
        JointPainterPathCreator(JointType type);

        // Inherited via IPainterPathCreator
        virtual QPainterPath getPath(QPointF begin, QPointF end) const override;

    private:
        void drawSphericalPath(Turtle& turtle, double length) const;
        void drawRevolutePath(Turtle& turtle, double length) const;
        void drawCylindricalPath(Turtle& turtle, double length) const;
        void drawSliderPath(Turtle& turtle, double length) const;
        void drawInlinePath(Turtle& turtle, double length) const;
        void drawUniversalPath(Turtle& turtle, double length) const;

        void drawAtpointPath(Turtle& turtle, double length) const;
        void drawConstantVelocityPath(Turtle& turtle, double length) const;
        void drawFixedPath(Turtle& turtle, double length)const;
        void drawInplanePath(Turtle& turtle, double length)const;
        void drawOrientationPath(Turtle& turtle, double length)const;
        void drawParallelPath(Turtle& turtle, double length)const;
        void drawPerpendicularPath(Turtle& turtle, double length)const;
        void drawPlanarPath(Turtle& turtle, double length)const;
        void drawScrewPath(Turtle& turtle, double length)const;

        //helper functions
        void drawTriangle(Turtle& turtle, double length)const;
        void drawCircle(Turtle& turtle, double length)const;
        void drawHalfCircle(Turtle& turtle, double length) const;
        void drawRectangle(Turtle& turtle, double width,double height)const;

        JointType m_type;
    };
}