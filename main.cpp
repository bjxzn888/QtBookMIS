#include "mainwindow.h"
#include "dbhelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbHelper *dbhelper = new DbHelper();
    dbhelper->createDbTable();
    MainWindow w;
    w.show();

    return a.exec();
}
