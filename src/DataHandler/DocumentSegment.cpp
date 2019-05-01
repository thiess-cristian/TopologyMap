#include "DataHandler\DocumentSegment.h"
#include "DataHandler\DocumentStrings.h"
#include "Version12.h"
#include "Version13.h"

using namespace DataHandler;

DocumentSegment::DocumentSegment(const QDomDocument & document):m_document(document)
{
    int version = m_document.firstChildElement().attribute("Version").toDouble();
    switch (version) {
        case 12: {
            m_version = std::make_unique<Version12>();
            break;
        }
        case 13: {
            m_version = std::make_unique<Version13>();
            break;
        }
        default: {
            m_version = std::make_unique<Version13>();
            break;
        }
    }
}

DataModel::Point3D DocumentSegment::readPoint(QDomElement origin)
{
    double x = origin.firstChildElement(Doc::X).attribute(Doc::Value).toDouble();
    double y = origin.firstChildElement(Doc::Y).attribute(Doc::Value).toDouble();
    double z = origin.firstChildElement(Doc::Z).attribute(Doc::Value).toDouble();

    return DataModel::Point3D(x, y, z);
}
