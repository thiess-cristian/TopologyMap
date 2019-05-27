#pragma once
#include <string>
#include <qfile.h>
#include <memory>
#include <DataModel\Mechanism.h>
#include <GraphicModel\Mechanism.h>

namespace App
{
    class TopologyMap
    {
    public:
        TopologyMap();

        void openElements(QFile& file);
        void saveElements(QFile& file, std::string modelName);
        void loadElements(QFile& file, std::string modelName);

        void displayElementName(DataModel::ElementType type, bool checked);

        std::shared_ptr<DataModel::Mechanism> getDataModel() const;
        std::shared_ptr<GM::Mechanism> getGraphicModel()const;

    private:
        std::shared_ptr<DataModel::Mechanism> m_dataModelMechansim;
        std::shared_ptr<GM::Mechanism> m_graphicModelMechansim;

    };
}