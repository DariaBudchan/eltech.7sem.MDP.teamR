#include "diagramscene.h"

DiagramScene::DiagramScene(QObject *parent)
    :QGraphicsScene(parent)
{
    mode = Move;
    current_type = 0;
    ConditionItem* ellipse = new ConditionItem();
    ellipse->setPos(60,60);
    this->addItem(ellipse);

    ProcessItem* rectangle = new ProcessItem();
    rectangle->setPos(200,200);
    this->addItem(rectangle);

    /*ArrowItem* arrow = new ArrowItem(rectangle, ellipse);
    this->addItem(arrow);
    arrow->updatePosition();*/

    ConditionItem* ellipse2 = new ConditionItem();
    ellipse2->setPos(100, 300);
    this->addItem(ellipse2);

   /* ArrowItem* arrow2 = new ArrowItem(ellipse2, rectangle);
    this->addItem(arrow2);
    arrow2->updatePosition();*/
}

DiagramScene::~DiagramScene()
{

}

void DiagramScene::drawItem(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem* item;
    switch (current_type) {
    case ConditionItem::Type:
        item = new ConditionItem();
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        break;
    case ProcessItem::Type:
        item = new ProcessItem();
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        break;
    default:
        break;
    }

    emit itemInserted(item);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;

    switch(mode){
    case Draw:
        drawItem(mouseEvent);
        break;
    case Line:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
        line->setPen(QPen(Qt::red,2));
        addItem(line);
        break;
    default:
        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
    update();
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mode == Line && line != 0){
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
    else
        if(mode == Move){
            QGraphicsScene::mousePressEvent(mouseEvent);
        }
    update();
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if(mode == Line && line != 0){
        QList<QGraphicsItem*> startItems = items(line->line().p1());
        if(startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem*> endItems = items(line->line().p2());
        if(endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
        if(startItems.count() > 0 && endItems.count() > 0){
            if(ConditionItem* sci = dynamic_cast<ConditionItem*> (startItems.first())){
                if(ProcessItem* epi = dynamic_cast<ProcessItem*> (endItems.first())){
                    ArrowItem* arrow = new ArrowItem(sci, epi);
                    sci->addArrow(arrow);
                    //!!!!!
                    arrow->updatePosition();
                    addItem(arrow);
                }
            }else
            if(ProcessItem* spi = dynamic_cast<ProcessItem*> (startItems.first())){
                if(ConditionItem* eci = dynamic_cast<ConditionItem*> (endItems.first())){
                    ArrowItem* arrow = new ArrowItem(spi, eci);
                    eci->addArrow(arrow);
                    //!!!!!!
                    arrow->updatePosition();
                    addItem(arrow);
                }
            }
        }
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    update();
}

void DiagramScene::itemChanged(QGraphicsItem* item){
    emit itemSelected(item);
}

void DiagramScene::setMode(DiagramScene::Mode newmode)
{
    mode = newmode;
}

void DiagramScene::setItemType(int type)
{
    current_type = type;
}

