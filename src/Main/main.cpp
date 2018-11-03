#include <qfile.h>
#include <qapplication.h>
#include "TopologyMapWindow.h"

int main(int argc, char *argv[])
{
    QFile file("D:/fac/siemens-project/resources/Mot_lms0267_E_aa_p_sub_jat_11.mdef");
    //QFile file("D:/fac/siemens-project/resources/test.xml");
    QApplication a(argc, argv);
    TopologyMapWindow w;
    w.show();

    return a.exec();
}