#include <qfile.h>
#include <qapplication.h>
#include "TopologyMapWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TopologyMapWindow w;
    w.show();

    return a.exec();
}