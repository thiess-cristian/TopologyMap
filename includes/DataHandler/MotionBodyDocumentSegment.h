#pragma once
#include "DataHandler\DocumentSegment.h"

namespace DataHandler
{
    class MotionBodyDocumentSegment :public DocumentSegment
    {
    public:
        MotionBodyDocumentSegment(const QDomDocument& document);
        virtual void readSegment(std::shared_ptr<DataModel::Mechanism> mechanism) override;
    };
}