#pragma once
#include "IPainterPathCreator.h"
#include "XMLTagNames.h"

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

    JointType m_type;

};