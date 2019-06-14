#pragma once
#include "GraphicModel\Element.h"
#include <qobject.h>

namespace GM
{
    class MotionBody:public QObject,public Element
    {
        Q_OBJECT
    public:
        MotionBody(std::shared_ptr<DataModel::Element> elementDataModel,const QRectF& body=QRect());

        // Inherited via Element
        virtual QRectF boundingRect() const override;
        virtual QPainterPath shape() const override;
        virtual void translate(QPointF translation) override;
        virtual void scale(double scaleFactor) override;

        virtual void scaleOrigin(double scaleFactor) override;

        void setBody(const QRectF& body);

        static const size_t MinWidth = 50;
        static const size_t MinHeight = 50;

    signals:
        void offsetChanged(QPointF dir);

    private:
        QRectF m_body;
    };
}