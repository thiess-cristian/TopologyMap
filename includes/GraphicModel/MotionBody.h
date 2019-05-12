#pragma once
#include "GraphicModel\Element.h"

namespace GM
{
    class MotionBody:public Element
    {
    public:
        MotionBody(std::shared_ptr<DataModel::Element> elementDataModel,const QRectF& body=QRect());

        // Inherited via Element
        virtual QRectF boundingRect() const override;
        virtual QPainterPath shape() const override;
        virtual void translate(QPointF translation) override;
        virtual void scale(double scaleFactor) override;

        void setBody(const QRectF& body);

        static const size_t MinWidth = 50;
        static const size_t MinHeight = 50;

    private:
        QRectF m_body;
    };
}