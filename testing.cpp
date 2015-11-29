#include "testing.h"

testing::testing()
{
    startTesting();
}

void testing::startTesting()
{
    //Create scene
    scene = new DiagramScene();
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    scene->setMode(DiagramScene::Move);
    view = new QGraphicsView(this);
    view->setScene(scene);
    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->setAlignment(Qt::AlignLeft);
    QHBoxLayout* workspace = new QHBoxLayout;
    workspace->setAlignment(Qt::AlignTop);
    workspace->addWidget(view);
    centralLayout->addItem(workspace);

    QWidget* central = new QWidget;
    central->setLayout(centralLayout);
    setCentralWidget(central);

    //Create emulator
    isOnWork = false;
    emulator = new PetriEmulator(scene, this);
    emulator->setWork(false);

    //Create items on scene
    ProcessItem* proItem1 = new ProcessItem();
    proItem1->setPos(-150, -100);
    scene->addItem(proItem1);

    ProcessItem* proItem2 = new ProcessItem();
    proItem2->setPos(-150, 100);
    scene->addItem(proItem2);

    ProcessItem* proItem3 = new ProcessItem();
    proItem3->setPos(150, 100);
    scene->addItem(proItem3);

    ProcessItem* proItem4 = new ProcessItem();
    proItem4->setPos(150, -100);
    scene->addItem(proItem4);

    ConditionItem* conItem1 = new ConditionItem();
    conItem1->setPos(-300, 0);
    scene->addItem(conItem1);

    ConditionItem* conItem2 = new ConditionItem();
    conItem2->setPos(0, 0);
    scene->addItem(conItem2);

    ConditionItem* conItem3 = new ConditionItem();
    conItem3->setPos(300, 0);
    scene->addItem(conItem3);

    ConditionItem* conItem4 = new ConditionItem();
    conItem4->setPos(0, 150);
    scene->addItem(conItem4);

    ConditionItem* conItem5 = new ConditionItem();
    conItem5->setPos(300, 150);
    scene->addItem(conItem5);

    //First while
    ArrowItem* arrow1 = new ArrowItem(proItem1, conItem1);
    proItem1->addArrow(arrow1);
    conItem1->addArrow(arrow1);
    arrow1->updatePosition();
    scene->addItem(arrow1);

    ArrowItem* arrow2 = new ArrowItem(conItem1, proItem2);
    conItem1->addArrow(arrow2);
    proItem2->addArrow(arrow2);
    arrow2->updatePosition();
    scene->addItem(arrow2);

    ArrowItem* arrow3 = new ArrowItem(proItem2, conItem2);
    proItem2->addArrow(arrow3);
    conItem2->addArrow(arrow3);
    arrow3->updatePosition();
    scene->addItem(arrow3);

    ArrowItem* arrow4 = new ArrowItem(conItem2, proItem1);
    conItem2->addArrow(arrow4);
    proItem1->addArrow(arrow4);
    arrow4->updatePosition();
    scene->addItem(arrow4);

    //Second while
    ArrowItem* arrow5 = new ArrowItem(proItem4, conItem2);
    proItem4->addArrow(arrow5);
    conItem2->addArrow(arrow5);
    arrow5->updatePosition();
    scene->addItem(arrow5);

    ArrowItem* arrow6 = new ArrowItem(conItem2, proItem3);
    conItem2->addArrow(arrow6);
    proItem3->addArrow(arrow6);
    arrow6->updatePosition();
    scene->addItem(arrow6);

    ArrowItem* arrow7 = new ArrowItem(proItem3, conItem3);
    proItem3->addArrow(arrow7);
    conItem3->addArrow(arrow7);
    arrow7->updatePosition();
    scene->addItem(arrow7);

    ArrowItem* arrow8 = new ArrowItem(conItem3, proItem4);
    conItem3->addArrow(arrow8);
    proItem4->addArrow(arrow8);
    arrow8->updatePosition();
    scene->addItem(arrow8);

    ArrowItem* arrow9 = new ArrowItem(proItem2, conItem4);
    proItem2->addArrow(arrow9);
    conItem4->addArrow(arrow9);
    arrow9->updatePosition();
    scene->addItem(arrow9);

    ArrowItem* arrow10 = new ArrowItem(proItem3, conItem4);
    proItem3->addArrow(arrow10);
    conItem4->addArrow(arrow10);
    arrow10->updatePosition();
    scene->addItem(arrow10);

    ArrowItem* arrow11 = new ArrowItem(proItem3, conItem5);
    proItem3->addArrow(arrow11);
    conItem5->addArrow(arrow11);
    arrow11->updatePosition();
    scene->addItem(arrow11);

    conItem2->increaseValue();

    qDebug() << "First test start.";
    for(int i = 0; i < 52; i++)
    {
        emulator->nextStep();
        scene->update();
        if(i == 1) continue; // It is correct behavior
        qDebug() << (i+1) << ")" << firstTest(conItem2, conItem4, conItem5);
    }
    qDebug() << "First test finish.";

    qDebug() << "Second test start.";
    for(int i = 0; i < 50; i++)
    {
        emulator->nextStep();
        scene->update();
        qDebug() << (i+1) << ")" << secondTest(conItem1, conItem2);
    }
    qDebug() << "Second test finish.";

    qDebug() << "Third test start.";
    for(int i = 0; i < 50; i++)
    {
        emulator->nextStep();
        scene->update();
        qDebug() << (i+1) << ")" << thirdTest(conItem1, conItem2, conItem3, conItem4, conItem5);
    }
    qDebug() << "Third test finish.";
}

QString testing::thirdTest(ConditionItem* conItem1 , ConditionItem* conItem2, ConditionItem* conItem3,
                  ConditionItem* conItem4, ConditionItem* conItem5)
{
    if(emulator->isValid()){
        if((conItem1->getValue() == 51) && (conItem2->getValue() == 0) && (conItem3->getValue() == 0) &&
                (conItem4->getValue() == 99) && (conItem5->getValue() == 50)){
            return "Test step pass !";
        }
        else{
            return "Test step fail !";
        }
    }
    else{
        return "Test valid fail !";
    }
    return "No value";
}

QString testing::secondTest(ConditionItem* conItem1 , ConditionItem* conItem2)
{
    if(emulator->isValid()){
        if((conItem1->getValue() + conItem2->getValue()) == 51){
            return "Test step pass !";
        }
        else{
            return "Test step fail !";
        }
    }
    else{
        return "Test valid fail !";
    }
    return "No value";
}

QString testing::firstTest(ConditionItem* conItem2 , ConditionItem* conItem4, ConditionItem* conItem5)
{
    if(emulator->isValid()){
        if((conItem2->getValue() + conItem5->getValue()) == conItem4->getValue()){
            return "Test step pass !";
        }
        else{
            return "Test step fail !";
        }
    }
    else{
        return "Test valid fail !";
    }
    return "No value";
}
