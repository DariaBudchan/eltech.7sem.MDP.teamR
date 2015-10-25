#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

#include "diagramscene.h"
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();*/
    DiagramScene* scene = new DiagramScene();
    scene->setSceneRect(0,0,1000,1000);
    QGraphicsView* view = new QGraphicsView();
    view->setScene(scene);
    view->show();
    return a.exec();
}
