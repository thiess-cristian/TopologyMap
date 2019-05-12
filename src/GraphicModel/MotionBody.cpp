#include "GraphicModel\MotionBody.h"
#include <DataModel\Element.h>
#include <qfontmetrics.h>
#include <qgraphicsitem.h>
#include <algorithm>

using namespace GM;

MotionBody::MotionBody(std::shared_ptr<DataModel::Element> elementDataModel, const QRectF& body):Element(elementDataModel),m_body(body)
{
    DefaultColor = QColor(128, 128, 255, 128);
}

QRectF MotionBody::boundingRect() const
{
    QRectF bounding = m_body;

    bounding.setWidth(std::max(bounding.width(), (double)MinWidth));
    bounding.setHeight(std::max(bounding.height(), (double)MinHeight));

    QGraphicsTextItem textItem;
    textItem.font();
    QFontMetrics metrics(textItem.font());
    int textLength = std::max(0, static_cast<int>(metrics.width(m_elementDataModel->getName().c_str()) - m_body.width() / 2));
    return bounding.adjusted(0, 0, textLength, 0);
}

QPainterPath MotionBody::shape() const
{
    return QPainterPath();
}

void MotionBody::translate(QPointF translation)
{
    m_body.translate(translation);
}

void MotionBody::scale(double scaleFactor)
{
    m_body = QRectF(m_body.x()*scaleFactor,
                    m_body.y()*scaleFactor,
                    m_body.width()*scaleFactor,
                    m_body.height()*scaleFactor);
}

void GM::MotionBody::setBody(const QRectF & body)
{
    m_body = body;
}
