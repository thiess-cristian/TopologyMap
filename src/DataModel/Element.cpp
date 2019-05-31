#include "DataModel\Element.h"

using namespace DataModel;

Element::Element(const std::string& name) :m_name(name)
{

}

std::string Element::getName()const
{
    return m_name;
}

bool Element::operator==(const Element & other) const
{
    return isEqual(other);
}

bool Element::operator!=(const Element & other) const
{
    return !(*this == other);
}

bool Element::isEqual(const Element&other) const
{
    return m_name == other.m_name;
}
