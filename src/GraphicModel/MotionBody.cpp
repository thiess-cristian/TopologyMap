#include "GraphicModel\MotionBody.h"
#include <DataModel\Element.h>
#include <GraphicView\Element.h>
#include <qfontmetrics.h>
#include <qgraphicsitem.h>
#include <algorithm>

using namespace GM;

MotionBody::MotionBody(std::shared_ptr<DataModel::Element> elementDataModel, const QRectF& body):Element(elementDataModel),m_body(body)
{
    DefaultColor = QColor(128, 128, 255, 128);
    m_color = DefaultColor;
}

QRectF MotionBody::boundingRect() const
{
    auto bounding = m_body;
    
    QGraphicsTextItem textItem;
    textItem.font();
    QFontMetrics metrics(textItem.font());
    int textWidth = std::max(static_cast<int>(bounding.width()), metrics.width(m_elementDataModel->getName().c_str()) + 20);
    bounding.setWidth(textWidth);

    double minWidth = textWidth;
    double minHeight = metrics.height() + 5;

    bounding.setWidth(std::max(bounding.width(), minWidth));
    bounding.setHeight(std::max(bounding.height(),minHeight));
    
    return bounding;
}

QPainterPath MotionBody::shape() const
{
    QPainterPath path;
    path.addRect(m_body);
    return path;
}

void MotionBody::translate(QPointF translation)
{
    m_graphicViewModel->prepareViewModel();
    m_body.translate(translation);
}

void MotionBody::scale(double scaleFactor)
{
    m_graphicViewModel->prepareViewModel();
    m_body = QRectF(m_body.x()*scaleFactor,
                    m_body.y()*scaleFactor,
                    m_body.width()*scaleFactor,
                    m_body.height()*scaleFactor);
}

void MotionBody::scaleOrigin(double scaleFactor)
{
    m_graphicViewModel->prepareViewModel();
    m_body = QRectF(m_body.x()*scaleFactor,
                    m_body.y()*scaleFactor,
                    m_body.width(),
                    m_body.height());    
}

void GM::MotionBody::setBody(const QRectF & body)
{
    m_body = body;
}
