#pragma once
#include "Version.h"
#include <DataModel\Mechanism.h>
#include <DataModel\Point3D.h>
#include <memory>
#include <qdom.h>

namespace DataHandler
{
    class DocumentSegment
    {
    public:
        DocumentSegment(const QDomDocument& document);
        virtual void readSegment(std::shared_ptr<DataModel::Mechanism> mechanism) = 0;
        

    protected:
        DataModel::Point3D readPoint(QDomElement origin);

        const QDomDocument& m_document;
        std::unique_ptr<Version> m_version;
    };


}