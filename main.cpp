#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QMessageBox messageBox;
    messageBox.critical(0,"Igor","I can commit Project !");
    messageBox.setFixedSize(500,200);
    w.show();

    return a.exec();
}
