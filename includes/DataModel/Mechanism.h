#pragma once
#include <memory>
#include <map>

namespace DataModel
{
    enum class ElementType
    {
        Element,
        Link,
        MotionBody,
        Connector,
        Joint
    };

    class Element;

    class Mechanism
    {
    public:
        Mechanism();

        void addDataContainer(std::map<std::string, std::shared_ptr<Element>> container, ElementType type);
        std::map<std::string, std::shared_ptr<Element>> getContainer(ElementType type) const;
        std::map<ElementType, std::map<std::string, std::shared_ptr<Element>>> getElements()const;

    private:
        std::map<ElementType, std::map<std::string, std::shared_ptr<Element>>> m_elements;
    };
}