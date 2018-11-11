#include "GraphicMotionBody.h"
#include "qpainter.h"

GraphicMotionBody::GraphicMotionBody(MotionBody body, Perspective perspective):
    m_motionBody(body),
    m_perspective(perspective),
    m_boundingRect(QRectF())
{
    setOriginRelatedToPerspective();
    setBoundingRectRelatedToPerspective();
}

QRectF GraphicMotionBody::boundingRect() const
{
    return m_boundingRect;
}

void GraphicMotionBody::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //QGraphicsItem::paint(painter, option, widget);

    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), m_motionBody.getName().c_str());

}

void GraphicMotionBody::setOriginRelatedToPerspective()
{
    switch (m_perspective) {
        case Perspective::TOP: {
            m_origin.setX(m_motionBody.getX());
            m_origin.setY(m_motionBody.getZ());
            break;
        }
        case Perspective::SIDE: {
            m_origin.setX(m_motionBody.getX());
            m_origin.setY(m_motionBody.getY());
            break;
        }
        case Perspective::FRONT: {
            m_origin.setX(m_motionBody.getZ());
            m_origin.setY(m_motionBody.getY());
            break;
        }
        default: {
            break;
        }
    }

}

void GraphicMotionBody::setBoundingRectRelatedToPerspective()
{
    double minX = DBL_MAX;
    double maxX = -DBL_MAX;
    double minY = DBL_MAX;
    double maxY = -DBL_MAX;
    auto connections = m_motionBody.getConnectionPoints();

    switch (m_perspective) {
        case Perspective::TOP: {
            for (const auto& point : connections) {
                if (point.getX() > maxX) {
                    maxX = point.getX();
                }

                if (point.getX() < minX) {
                    minX = point.getX();
                }

                if (point.getZ() > maxY) {
                    maxY = point.getZ();
                }

                if (point.getZ() < minY) {
                    minY = point.getZ();
                }
            }
            break;
        }
        case Perspective::SIDE: {
            for (const auto& point : connections) {
                if (point.getX() > maxX) {
                    maxX = point.getX();
                }

                if (point.getX() < minX) {
                    minX = point.getX();
                }

                if (point.getY() > maxY) {
                    maxY = point.getY();
                }

                if (point.getY() < minY) {
                    minY = point.getY();
                }
            }
            break;
        }
        case Perspective::FRONT: {
            for (const auto& point : connections) {
                if (point.getZ() > maxX) {
                    maxX = point.getZ();
                }

                if (point.getZ() < minX) {
                    minX = point.getZ();
                }

                if (point.getY() > maxY) {
                    maxY = point.getY();
                }

                if (point.getY() < minY) {
                    minY = point.getY();
                }
            }
            break;
        }
        default: {
            break;
        }
    }
    m_boundingRect = QRectF(minX, minY, maxX-minX, maxY-minY);
}
