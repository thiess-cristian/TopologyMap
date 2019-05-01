#include "DataModel\Mechanism.h"

using namespace DataModel;

Mechanism::Mechanism()
{
    
}

void Mechanism::addDataContainer(std::map<std::string, std::shared_ptr<Element>> container, ElementType type)
{
    m_elements[type] = container;
}

std::map<std::string, std::shared_ptr<Element>> Mechanism::getContainer(ElementType type) const
{
    return m_elements.at(type);
}
