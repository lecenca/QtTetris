#include <QApplication>

#include "MainSurface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSurface w;
    w.show();

    return a.exec();
}
