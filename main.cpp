#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /************Testing**************
        testing t;
        t.show();
    */

    /**********MainWindow************/
    MainWindow w;
    w.show();
    return a.exec();
}
