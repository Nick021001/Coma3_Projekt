#include "BildWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BildWidget w;
    w.show();
    return a.exec();
}
