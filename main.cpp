#include "mainhandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainhandler w;
    w.show();

    return a.exec();
}
