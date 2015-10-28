#include "diagramscene.h"

DiagramScene::DiagramScene(QObject *parent)
    :QGraphicsScene(parent)
{
    ConditionItem* ellipse = new ConditionItem();
    ellipse->setPos(60,60);
    this->addItem(ellipse);

    ProcessItem* rectangle = new ProcessItem();
    rectangle->setPos(52,100);
    this->addItem(rectangle);
}

DiagramScene::~DiagramScene()
{

}

