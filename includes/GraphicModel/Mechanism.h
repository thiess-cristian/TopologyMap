#pragma once
#include <DataModel\Mechanism.h>

namespace DataModel
{
    class Mechanism;
}

namespace GM
{
    class Element;
    class Mechanism
    {
    public:
        Mechanism(std::shared_ptr<DataModel::Mechanism> dataMechanism);
        std::map<DataModel::ElementType, std::map<std::string, std::shared_ptr<Element>>> getElements()const;

    private:
        std::map<DataModel::ElementType, std::map<std::string, std::shared_ptr<Element>>> m_elements;
    };


}