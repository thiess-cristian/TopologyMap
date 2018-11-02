#include "DocumentParser.h"
#include <qfile.h>

int main()
{
    QFile file("D:/fac/siemens-project/resources/test.xml");
    DocumentParser d(file);

    d.getMotionBodies();
    return 0;
}