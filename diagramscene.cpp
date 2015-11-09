#include "diagramscene.h"

DiagramScene::DiagramScene(QObject *parent)
    :QGraphicsScene(parent)
{
    mode = Move;
    current_type = 0;
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

void DiagramScene::addArrow(QGraphicsItem *start, QGraphicsItem *end)
{
    bool flag = true;

    if(ConditionItem* sci = dynamic_cast<ConditionItem*> (start)){
        if(ProcessItem* epi = dynamic_cast<ProcessItem*> (end)){
            QList<ArrowItem*> list1 = sci->getArrows();
            if(list1.count() > 0){
                foreach (ArrowItem* temp_arrow, list1){
                    if(((temp_arrow->getStart() == sci && temp_arrow->getEnd() == epi)
                        || (temp_arrow->getStart() == epi && temp_arrow->getEnd() == sci))){
                       flag = false;
                       break;
                    }
                }
            }
            else{
                flag = true;
            }

            if(flag){
                ArrowItem* arrow = new ArrowItem(sci, epi);
                sci->addArrow(arrow);
                epi->addArrow(arrow);
                arrow->updatePosition();
                addItem(arrow);
            }
        }
    }

    if(ProcessItem* spi = dynamic_cast<ProcessItem*> (start)){
        if(ConditionItem* eci = dynamic_cast<ConditionItem*> (end)){
            QList<ArrowItem*> list1 = eci->getArrows();
            if(list1.count() > 0){
                foreach (ArrowItem* temp_arrow, list1){
                    if(((temp_arrow->getStart() == spi && temp_arrow->getEnd() == eci)
                        || (temp_arrow->getStart() == eci && temp_arrow->getEnd() == spi))){
                       flag = false;
                       break;
                    }
                }
            }
            else{
                flag = true;
            }

            if(flag){
                ArrowItem* arrow = new ArrowItem(spi, eci);
                spi->addArrow(arrow);
                eci->addArrow(arrow);
                arrow->updatePosition();
                addItem(arrow);
            }
        }
    }
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
            addArrow(startItems.first(), endItems.first());
        }
       /* if(startItems.count() > 0 && endItems.count() > 0){
            if(ConditionItem* sci = dynamic_cast<ConditionItem*> (startItems.first())){
                if(ProcessItem* epi = dynamic_cast<ProcessItem*> (endItems.first())){
                    foreach (ArrowItem* temp_arrow, sci->getArrows()) {
                        if(!((temp_arrow->getStart() == sci && temp_arrow->getEnd() == epi) ||
                            temp_arrow->getStart() == epi && temp_arrow->getEnd() == sci)){
                            ArrowItem* arrow = new ArrowItem(sci, epi);
                            sci->addArrow(arrow);
                            epi->addArrow(arrow);
                            arrow->updatePosition();
                            addItem(arrow);
                        }
                    }
                }
            }else
            if(ProcessItem* spi = dynamic_cast<ProcessItem*> (startItems.first())){
                if(ConditionItem* eci = dynamic_cast<ConditionItem*> (endItems.first())){
                    foreach (ArrowItem* temp_arrow, spi->getArrows()) {
                        if(!((temp_arrow->getStart() == spi && temp_arrow->getEnd() == eci) ||
                            temp_arrow->getStart() == eci && temp_arrow->getEnd() == spi)){
                            ArrowItem* arrow = new ArrowItem(spi, eci);
                            spi->addArrow(arrow);
                            eci->addArrow(arrow);
                            arrow->updatePosition();
                            addItem(arrow);
                        }
                    }
                }
            }
        }*/
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

