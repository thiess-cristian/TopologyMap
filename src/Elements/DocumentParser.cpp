#include "DocumentParser.h"
#include "qfile.h"

#include <string>

DocumentParser::DocumentParser(QFile& file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw "can't open";
    }

    if (!m_document.setContent(&file)) {
        throw "can't load file";
    }

    file.close();
    m_root = m_document.firstChildElement();
}

DocumentParser::~DocumentParser()
{

}

std::vector<MotionBody> DocumentParser::getMotionBodies() const
{
    QDomElement motionbodiesParent = m_root.firstChildElement("MotionBodies");

    QDomNodeList list = motionbodiesParent.elementsByTagName("MotionBody");

    std::vector<MotionBody> motionbodies(list.size());

    for (size_t i = 0; i < list.size();i++) {
        QDomNode item = list.at(i);

        std::string nameAttribute = item.toElement().attribute("Name").toStdString();
        motionbodies[i] = MotionBody(nameAttribute);

    }

    return motionbodies;
}


