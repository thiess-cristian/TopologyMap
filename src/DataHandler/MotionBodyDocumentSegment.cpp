#include "DataHandler\MotionBodyDocumentSegment.h"
#include "DataHandler\DocumentStrings.h"
#include <DataModel\MotionBody.h>


using namespace DataHandler;

MotionBodyDocumentSegment::MotionBodyDocumentSegment(const QDomDocument & document):DocumentSegment(document)
{}

void MotionBodyDocumentSegment::readSegment(std::shared_ptr<DataModel::Mechanism> mechanism)
{
    using namespace Doc;

    auto root = m_document.firstChildElement();
    const auto& version = *m_version;

    QDomElement motionbodiesParent = root.firstChildElement(version(MotionBodies));
    QDomNodeList list = motionbodiesParent.elementsByTagName(version(MotionBody));

    std::map<std::string, std::shared_ptr<DataModel::Element>> motionBodies;

    for (int i = 0; i < list.size(); i++) {
        QDomElement item = list.at(i).toElement();

        std::string nameAttribute = item.attribute(Name).toStdString();

        QDomElement origin = item.firstChildElement(MassAndInertia).firstChildElement(TransformationMatrix).firstChildElement(Origin);

        DataModel::Point3D originPoint = readPoint(origin);

        motionBodies[nameAttribute] = std::make_shared<DataModel::MotionBody>(nameAttribute, originPoint);
    }

    motionBodies["Ground"] = std::make_shared<DataModel::MotionBody>("Ground");

    mechanism->addDataContainer(motionBodies, DataModel::ElementType::MotionBody);
}
