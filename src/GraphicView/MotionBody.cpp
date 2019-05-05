#include "GraphicView\MotionBody.h"
#include "GraphicModel\Element.h"
#include "GraphicModel\MotionBody.h"

#include <qcursor.h>

using namespace GV;

MotionBody::MotionBody(std::shared_ptr<GM::Element> elementModel):Element(elementModel)
{

}

void MotionBody::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    auto dir = event->pos() - m_shiftMouseCoords;
    auto motionBodyModel = std::dynamic_pointer_cast<GM::MotionBody>(m_elementModel);
    motionBodyModel->bodyTranslate(dir);
    m_shiftMouseCoords = event->pos();

    //TODO:
    //emit offsetChanged(dir);
}

void MotionBody::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    m_shiftMouseCoords = event->pos();
    m_elementModel->setColor(m_elementModel->getColor().darker(200));
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void MotionBody::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    m_elementModel->setColor(m_elementModel->getColor().lighter(200));
    setCursor(QCursor(Qt::OpenHandCursor));
}
