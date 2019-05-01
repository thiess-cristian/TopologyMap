#pragma once
#include "DocumentSegment.h"

namespace DataHandler
{
    class JointDocumentSegment:public DocumentSegment
    {
    public:
        JointDocumentSegment(const QDomDocument& document);
        virtual void readSegment(std::shared_ptr<DataModel::Mechanism> mechanism) override;

    };


}