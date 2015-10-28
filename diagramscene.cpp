#include "diagramscene.h"

DiagramScene::DiagramScene(QObject *parent)
    :QGraphicsScene(parent)
{
    ConditionItem* ellipse = new ConditionItem();
    ellipse->setPos(60,60);
    this->addItem(ellipse);

    ProcessItem* rectangle = new ProcessItem();
    rectangle->setPos(200,200);
    this->addItem(rectangle);

    ArrowItem* arrow = new ArrowItem(rectangle, ellipse);
    this->addItem(arrow);
    arrow->updatePosition();
}

DiagramScene::~DiagramScene()
{

}

void DiagramScene::itemChanged(QGraphicsItem* item){
    emit itemSelected(item);
}

