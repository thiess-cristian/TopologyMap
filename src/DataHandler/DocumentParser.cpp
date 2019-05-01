#include "DataHandler\DocumentParser.h"
#include "DataHandler\ConnectorDocumentSegment.h"
#include "DataHandler\JointDocumentSegment.h"
#include "DataHandler\MotionBodyDocumentSegment.h"
#include <DataModel\Mechanism.h>
#include "qfile.h"

using namespace DataHandler;

DocumentParser::DocumentParser()
{
    m_mechanism = std::make_shared<DataModel::Mechanism>();
}

std::shared_ptr<DataModel::Mechanism> DataHandler::DocumentParser::parseFile(QFile & file)
{
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw "can't open";
    }

    if (!m_document.setContent(&file)) {
        throw "can't load file";
    }

    file.close();
    m_documentSegments.emplace_back(std::make_shared<MotionBodyDocumentSegment>(m_document));
    m_documentSegments.emplace_back(std::make_shared<JointDocumentSegment>(m_document));
    m_documentSegments.emplace_back(std::make_shared<ConnectorDocumentSegment>(m_document));

    for (const auto& segment : m_documentSegments) {
        segment->readSegment(m_mechanism);
    }
    
    return m_mechanism;
}
