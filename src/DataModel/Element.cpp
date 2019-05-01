#include "DataModel\Element.h"

using namespace DataModel;

Element::Element(const std::string& name) :m_name(name)
{

}

std::string Element::getName()const
{
    return m_name;
}
