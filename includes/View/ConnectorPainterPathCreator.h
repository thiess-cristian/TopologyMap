#pragma once
#include "IPainterPathCreator.h"
#include "XMLTagNames.h"

class Turtle;

class ConnectorPainterPathCreator :public IPainterPathCreator
{
public:
    ConnectorPainterPathCreator(ConnectorKind kind);
    // Inherited via IPainterPathCreator
    virtual QPainterPath getPath(QPointF begin, QPointF end) const override;

private:

    void drawSpringPath(Turtle& turtle,double length) const;
    void drawDamperPath(Turtle& turtle,double length) const;

    ConnectorKind m_kind;

};