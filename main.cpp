#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Q_INIT_RESOURCE(rc);

    return a.exec();
}
