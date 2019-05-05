#include "..\..\includes\GraphicView\Element.h"
#include "..\..\includes\GraphicView\Element.h"
#include "GraphicModel\Element.h"
#include <DataModel\Element.h>

using namespace GM;

Element::Element(std::shared_ptr<DataModel::Element> elementDataModel)
{

    
}


void Element::setColor(const QColor & color)
{
    m_color = color;
}

QColor Element::getColor() const
{
    return m_color;
}

std::shared_ptr<DataModel::Element> Element::getDataModel() const
{
    return m_elementDataModel;
}

bool Element::isDisplayingName() const
{
    return m_displayName;
}

bool Element::operator==(const Element & other)
{
    return *m_elementDataModel == *other.m_elementDataModel;
}
