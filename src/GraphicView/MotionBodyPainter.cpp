#include "GraphicView\MotionBodyPainter.h"
#include "GraphicModel\MotionBody.h"
#include "DataModel\Element.h"
#include <qpen.h>
#include <qpainter.h>
#include <qgraphicsitem.h>

using namespace GV;

MotionBodyPainter::MotionBodyPainter(std::shared_ptr<GM::MotionBody> motionBodyModel):m_motionBodyModel(motionBodyModel)
{
    
}

void MotionBodyPainter::paintItem(QPainter * painter) const
{
    QPen pen(Qt::black);
    pen.setCosmetic(true);
    painter->setPen(pen);

    auto bounding = m_motionBodyModel->boundingRect();
    QRectF rect(bounding.x(), bounding.y(), bounding.width(), bounding.height());

    double minWidth = 50;
    double minHeight = 50;

    rect.setWidth(std::max(rect.width(), minWidth));

    QGraphicsTextItem textItem;
    textItem.font();
    QFontMetrics metrics(textItem.font());
    int textWidth = std::max(static_cast<int>(rect.width()), metrics.width(m_motionBodyModel->getDataModel()->getName().c_str()) + 20);
    rect.setWidth(textWidth);

    
    painter->fillRect(rect, QBrush(m_motionBodyModel->getColor()));
    painter->drawRect(rect);
    if (m_motionBodyModel->isDisplayingName()) {        
        painter->drawText(bounding.topLeft() + QPoint(10, 13), m_motionBodyModel->getDataModel()->getName().c_str());
    }
}
