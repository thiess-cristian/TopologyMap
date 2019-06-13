#pragma once
#include <memory>
#include <qcolor.h>
#include <qrect.h>
#include <qpainterpath.h>

namespace DataModel
{
    class Element;
}

namespace GV
{
    class Element;
}

namespace GM
{
    class Element
    {
    public:
        Element(std::shared_ptr<DataModel::Element> elementDataModel);
        ~Element();

        void setColor(const QColor& color);
        QColor getColor()const;

        std::shared_ptr<DataModel::Element> getDataModel() const;

        void setGraphicViewModel(GV::Element* element);

        virtual QRectF boundingRect() const = 0;
        virtual QPainterPath shape() const = 0;
        virtual void translate(QPointF point) = 0;
        virtual void scale(double factor) = 0;

        bool isDisplayingName()const;
        void enableDisplayingName(bool checked);

        bool operator==(const Element& other);

        QColor DefaultColor;
    protected:
        QColor m_color;
        bool m_displayName = true;
        std::shared_ptr<DataModel::Element> m_elementDataModel;
        GV::Element* m_graphicViewModel;
    };
}