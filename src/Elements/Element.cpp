#include "Elements\Element.h"

Element::Element(const std::string& name):m_name(name)
{

}

std::string Element::getName()const
{
    return m_name;
}

bool Element::operator==(const Element& other)
{
    return m_name == other.m_name;
}

bool Element::operator!=(const Element & other)
{
    return !(*this == other);
}
