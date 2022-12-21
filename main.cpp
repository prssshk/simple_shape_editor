#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //var 74,4
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1280,900);
    w.show();
    return a.exec();
}
