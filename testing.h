#ifndef TESTING_H
#define TESTING_H

#include "arrowitem.h"
#include "conditionitem.h"
#include "diagramscene.h"
#include "petriemulator.h"
#include "processitem.h"
#include "mainwindow.h"

class testing : public QMainWindow
{
    DiagramScene* scene;
    QGraphicsView* view;
    PetriEmulator* emulator;
    bool isOnWork;
public:
    testing();
private slots:
    void startTesting();
};

#endif // TESTING_H
