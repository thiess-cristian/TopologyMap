#pragma once
#include "GraphicModel\Element.h"
#include <qpoint.h>
#include <qobject.h>

namespace GM
{
    class Element;

    class Link:public QObject,public Element
    {
        Q_OBJECT
    public:
        Link(std::shared_ptr<DataModel::Element> linkDataModel,
             std::shared_ptr<Element> actionGraphicModel, 
             std::shared_ptr<Element> baseGraphicModel);

        void setOverlappingCount(size_t i);
        size_t getOverlappingCount();

        void setReverseOverlaps(bool reverseOverlaps);
        bool isReverseOverlap();

        QPointF getActionConnection()const;
        QPointF getBaseConnection()const;

        void setActionConnection(const QPointF& action);
        void setBaseConnection(const QPointF& base);

        bool overlaps(const Link& other);
        bool reverseOverlaps(const Link& other);

        // Inherited via Element
        virtual QRectF boundingRect() const override;
        virtual QPainterPath shape() const override;
        virtual void translate(QPointF translate) override;
        virtual void scale(double scaleFactor) override;
        virtual void scaleOrigin(double scaleFactor) override;

    public slots:
        void offsetBasePosition(const QPointF& offset);
        void offsetActionPosition(const QPointF& offset);

    protected:
        QPointF m_actionConnection;
        QPointF m_baseConnection;

        size_t m_overlappingCount = 0;
        bool m_reverseOverlap = false;

        std::shared_ptr<Element> m_actionGraphicModel;
        std::shared_ptr<Element> m_baseGraphicModel;
    };
}