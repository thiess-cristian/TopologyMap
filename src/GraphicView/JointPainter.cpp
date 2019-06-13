#include "GraphicView\JointPainter.h"
#include "GraphicView\JointPainterPathCreator.h"
#include "GraphicModel\Joint.h"
#include "DataModel\Joint.h"
#include <qpen.h>
#include <qpainter.h>

using namespace GV;

JointPainter::JointPainter(std::shared_ptr<GM::Joint> jointModel):m_jointModel(jointModel)
{

}

void JointPainter::paintItem(QPainter * painter) const
{
    QPointF begin = m_jointModel->getActionConnection();
    QPointF end = m_jointModel->getBaseConnection();

    QPointF dir = end - begin;
    QPointF perpendicular(-1 * dir.y(), dir.x());

    double length = sqrt(pow(perpendicular.x(), 2) + pow(perpendicular.y(), 2));

    if (length != 0) {
        perpendicular /= length;

        auto overlappingCount = m_jointModel->getOverlappingCount();
        int xPositionOffset = (overlappingCount - overlappingCount % 2)/2;        
        xPositionOffset *= overlappingCount % 2 == 0 ? 1 : -1;
        xPositionOffset -= overlappingCount % 2;
        int yPositionOffset = overlappingCount;

        if (m_jointModel->isReverseOverlap()) {
            xPositionOffset *= -1;
        }

        begin += perpendicular*xPositionOffset * 10;
        begin += dir*yPositionOffset*0.05;
        end += perpendicular*xPositionOffset * 10;
        end -= dir*yPositionOffset*0.05;
    }

    auto dataModel = std::dynamic_pointer_cast<DataModel::Joint>(m_jointModel->getDataModel());
    JointPainterPathCreator creator(dataModel->getType());

    QPainterPath path;
    path.moveTo(m_jointModel->getActionConnection());
    path.lineTo(begin);
    path.addPath(creator.getPath(begin, end));
    path.lineTo(m_jointModel->getBaseConnection());

    QPen pen(m_jointModel->getColor());
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPath(path);
    painter->drawEllipse(m_jointModel->getActionConnection(), 5, 5);
    painter->drawEllipse(m_jointModel->getBaseConnection(), 7, 7);

    if (m_jointModel->isDisplayingName()) {        
        painter->drawText(m_jointModel->boundingRect().center() + QPoint(10, 10), dataModel->getName().c_str());
    }
}
