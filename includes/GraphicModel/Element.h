#pragma once
#include <memory>
#include <qcolor.h>
#include <qrect.h>
#include <qpainterpath.h>

namespace DataModel
{
    class Element;
}

namespace GM
{
    class Element
    {
    public:
        Element(std::shared_ptr<DataModel::Element> elementDataModel);

        void setColor(const QColor& color);
        QColor getColor()const;

        std::shared_ptr<DataModel::Element> getDataModel() const;

        virtual QRectF boundingRect()const = 0;
        virtual QPainterPath shape()const = 0;

        bool isDisplayingName()const;

        bool operator==(const Element& other);

        QColor DefaultColor;
    protected:
        QColor m_color;
        bool m_displayName;
        std::shared_ptr<DataModel::Element> m_elementDataModel;
    };


}