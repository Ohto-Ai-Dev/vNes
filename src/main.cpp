#include "VirtualNES.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VirtualNES w;
    w.show();
    return a.exec();
}
