#pragma once 
#include <vector>
#include <qdom.h>
#include <MotionBody.h>

class QFile;

class DocumentParser
{
public:
    DocumentParser(QFile& file);
    ~DocumentParser();
    
    std::vector<MotionBody> getMotionBodies() const;

private:
    QDomDocument m_document;
    QDomElement m_root;

};