#pragma once
#include "DataHandler\DocumentSegment.h"

namespace DataHandler
{
    class ConnectorDocumentSegment :public DocumentSegment
    {
    public:
        ConnectorDocumentSegment(const QDomDocument& document);
        virtual void readSegment(std::shared_ptr<DataModel::Mechanism> mechanism) override;
    };


}