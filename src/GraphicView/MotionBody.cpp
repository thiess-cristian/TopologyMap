#include "GraphicView\MotionBody.h"
#include "GraphicModel\Element.h"
#include "GraphicModel\MotionBody.h"
#include "GraphicView\MotionBodyPainter.h"

#include <qcursor.h>

using namespace GV;

MotionBody::MotionBody(std::shared_ptr<GM::Element> elementModel):Element(elementModel)
{
    m_elementPainter = std::make_unique<MotionBodyPainter>(std::dynamic_pointer_cast<GM::MotionBody>(m_elementModel));
}

void MotionBody::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    prepareGeometryChange();
    auto dir = event->pos() - m_shiftMouseCoords;    
    m_elementModel->translate(dir);
    m_shiftMouseCoords = event->pos();
    
    //TODO:
    auto model = std::dynamic_pointer_cast<GM::MotionBody>(m_elementModel);
    emit model->offsetChanged(dir);
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
