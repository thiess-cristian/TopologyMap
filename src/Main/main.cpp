#include <qfile.h>
#include <qapplication.h>
#include "TopologyMapWindow.h"
#include <random>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    TopologyMapWindow w;
    w.show();

    return a.exec();
}