#include "GraphicModel\Link.h"
#include "GraphicModel\Bounder.h"

using namespace GM;

Link::Link(std::shared_ptr<DataModel::Element> elementDataModel,
           std::shared_ptr<Element> actionGraphicModel,
           std::shared_ptr<Element> baseGraphicModel):
    Element(elementDataModel),
    m_actionGraphicModel(actionGraphicModel),
    m_baseGraphicModel(baseGraphicModel)
{
    
}

void Link::setOverlappingCount(size_t i)
{
    m_overlappingCount = i;
}

size_t Link::getOverlappingCount()
{
    return m_overlappingCount;
}

void Link::setReverseOverlaps(bool reverseOverlaps)
{
    m_reverseOverlap = reverseOverlaps;
}

bool Link::isReverseOverlap()
{
    return m_reverseOverlap;
}

void Link::setActionConnection(const QPointF & action)
{
    m_actionConnection = action;
}

void Link::setBaseConnection(const QPointF & base)
{
    m_baseConnection = base;
}

bool Link::overlaps(const Link & other)
{
    return *m_actionGraphicModel == *other.m_actionGraphicModel && *m_baseGraphicModel == *other.m_baseGraphicModel;
}

bool Link::reverseOverlaps(const Link & other)
{
    return *m_actionGraphicModel == *other.m_baseGraphicModel && *m_baseGraphicModel == *other.m_actionGraphicModel;
}

void Link::translate(QPointF translate)
{
    m_baseConnection += translate;
    m_actionConnection += translate;
}

void Link::scale(double scaleFactor)
{
    m_baseConnection *= scaleFactor;
    m_actionConnection *= scaleFactor;
}

void Link::offsetBasePosition(const QPointF & offset)
{
    m_baseConnection += offset;
}

void Link::offsetActionPosition(const QPointF & offset)
{
    m_actionConnection += offset;
}

QRectF Link::boundingRect() const
{
    Bounder bounder;
    return  bounder.createBoundingRect({m_actionConnection,m_baseConnection}).adjusted(-8, -8, 8, 8);
}

QPainterPath Link::shape() const
{
    QPointF begin(m_actionConnection.x(), m_actionConnection.y());
    QPointF end(m_baseConnection.x(), m_baseConnection.y());

    double dx = std::max(begin.x(), end.x()) - std::min(begin.x(), end.x());
    double dy = std::max(begin.y(), end.y()) - std::min(begin.y(), end.y());

    double width = 25;
    double d = sqrt(dx*dx + dy*dy);

    dx = 0.5*width*dx / d;
    dy = 0.5*width*dy / d;

    QPointF A(begin.x() - dy, begin.y() + dx);
    QPointF B(begin.x() + dy, begin.y() - dx);
    QPointF C(end.x() - dy, end.y() + dx);
    QPointF D(end.x() + dy, end.y() - dx);

    QPainterPath shape;
    shape.moveTo(A);
    shape.lineTo(B);
    shape.lineTo(D);
    shape.lineTo(C);
    shape.lineTo(A);

    return shape;
}
