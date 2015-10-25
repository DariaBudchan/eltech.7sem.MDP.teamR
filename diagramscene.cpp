#include "diagramscene.h"

DiagramScene::DiagramScene(QObject *parent)
    :QGraphicsScene(parent)
{
    ConditionItem* ellipse = new ConditionItem();
    ellipse->setPos(60,60);
    this->addItem(ellipse);
}

DiagramScene::~DiagramScene()
{

}

