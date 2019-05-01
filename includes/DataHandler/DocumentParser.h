#pragma once
#include "Version.h"
#include <DataModel\Mechanism.h>
#include <memory>
#include <vector>
#include <qdom.h>
class QFile;

namespace DataHandler
{
    class DocumentSegment;

    class DocumentParser
    {
    public:
        DocumentParser();

        std::shared_ptr<DataModel::Mechanism> parseFile(QFile& file);

    private:
        QDomDocument m_document;
        QDomElement m_root;

        std::vector<std::shared_ptr<DocumentSegment>> m_documentSegments;

        std::unique_ptr<Version> m_version;
        std::shared_ptr<DataModel::Mechanism> m_mechanism;
    };
}