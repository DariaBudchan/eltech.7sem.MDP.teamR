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
    QString firstTest(ConditionItem* conItem2 , ConditionItem* conItem4, ConditionItem* conItem5);
    QString secondTest(ConditionItem* conItem1 , ConditionItem* conItem2);
    QString thirdTest(ConditionItem* conItem1 , ConditionItem* conItem2, ConditionItem* conItem3,
                      ConditionItem* conItem4, ConditionItem* conItem5);
    void startTesting();
};

#endif // TESTING_H
