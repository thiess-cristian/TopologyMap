#include "GraphicView\ConnectorPainter.h"
#include "GraphicView\ConnectorPainterPathCreator.h"
#include "GraphicModel\Connector.h"
#include "DataModel\Connector.h"
#include <qpen.h>
#include <qpainter.h>

using namespace GV;

ConnectorPainter::ConnectorPainter(std::shared_ptr<GM::Connector> connectorModel):m_connectorModel(connectorModel)
{}

void ConnectorPainter::paintItem(QPainter * painter) const
{
    QPointF begin = m_connectorModel->getActionConnection();
    QPointF end = m_connectorModel->getBaseConnection();

    QPointF dir = end - begin;
    QPointF perpendicular(-1 * dir.y(), dir.x());

    double length = sqrt(pow(perpendicular.x(), 2) + pow(perpendicular.y(), 2));

    if (length != 0) {

        perpendicular /= length;
        auto overlappingCount=m_connectorModel->getOverlappingCount();
        int xPositionOffset = overlappingCount - overlappingCount % 2;
        xPositionOffset *= overlappingCount % 2 ? 1 : -1;
        int yPositionOffset = overlappingCount;

        if (m_connectorModel->isReverseOverlap()) {
            xPositionOffset *= -1;
        }

        begin += perpendicular*xPositionOffset * 10;
        begin += dir*yPositionOffset*0.05;
        end += perpendicular*xPositionOffset * 10;
        end -= dir*yPositionOffset*0.05;
    }

    auto dataModel = std::dynamic_pointer_cast<DataModel::Connector>(m_connectorModel->getDataModel());
    
    ConnectorPainterPathCreator creator(dataModel->getKind());

    QPainterPath path;
    path.moveTo(m_connectorModel->getActionConnection());
    path.lineTo(begin);
    path.addPath(creator.getPath(begin, end));
    path.lineTo(m_connectorModel->getBaseConnection());

    QPen pen(m_connectorModel->getColor());
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPath(path);
    if (m_connectorModel->isDisplayingName()) {
        QPointF middlePoint((begin + end) / 2);
        painter->drawText(middlePoint + QPoint(10, 10), dataModel->getName().c_str());
    }
}
