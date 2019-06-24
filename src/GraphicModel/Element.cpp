#include "GraphicView\Element.h"
#include "GraphicView\Element.h"
#include "GraphicModel\Element.h"
#include <DataModel\Element.h>
#include <iostream>

using namespace GM;

Element::Element(std::shared_ptr<DataModel::Element> elementDataModel):m_elementDataModel(elementDataModel)
{
   
}

Element::~Element()
{
    
}

void Element::setColor(const QColor & color)
{
    m_graphicViewModel->prepareViewModel();
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

void Element::setGraphicViewModel(GV::Element * element)
{
    m_graphicViewModel = element;
}

bool Element::isDisplayingName() const
{
    return m_displayName;
}

void Element::enableDisplayingName(bool checked)
{
    m_graphicViewModel->prepareViewModel();
    m_displayName = checked;
}

bool Element::operator==(const Element & other)
{
    return *m_elementDataModel == *other.m_elementDataModel;
}
