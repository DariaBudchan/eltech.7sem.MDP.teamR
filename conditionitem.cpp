#include "conditionitem.h"
#include "diagramscene.h"

#define PI 3.1415

ConditionItem::ConditionItem(QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
    current_value = 0;
    this->setRect(-25,-25,50,50);
    this->setBrush(QColor::fromRgbF(0.9,0.9,0.9));
    this->setPen(QPen(QColor::fromRgbF(0,0,0)));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void ConditionItem::increaseValue()
{
    current_value++;
    contectDraw(current_value);
}

void ConditionItem::decreaseValue()
{
    if(current_value != 0){
        current_value--;
    }
    contectDraw(current_value);
}

void ConditionItem::setValue(unsigned int value)
{
    current_value = value;
    contectDraw(current_value);
}

unsigned int ConditionItem::getValue()
{
    return current_value;
}

void ConditionItem::removeArrow(ArrowItem *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void ConditionItem::removeArrows()
{
    foreach (ArrowItem *arrow, arrows) {
        arrow->disconnect();
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void ConditionItem::addArrow(ArrowItem *arrow)
{
    arrows.append(arrow);
}

QList<ArrowItem *> ConditionItem::getArrows()
{
    return arrows;
}

void ConditionItem::contectDraw(unsigned int value)
{
    QList<QGraphicsItem*> list0 = this->childItems();
    foreach (QGraphicsItem* item, list0) {
        delete item;
    }

    if(value == 0){
        return;
    }

    QGraphicsEllipseItem* elitem;

    if(value == 1){
        elitem = new QGraphicsEllipseItem();
        elitem->setParentItem(this);
        elitem->setRect(-9,-9,18,18);
        elitem->setBrush(QColor::fromRgbF(0,0,0));
        elitem->setPen(QPen(QColor::fromRgbF(0,0,0)));
        return;
    }

    if(value >= 5){
        TextItem* text = new TextItem(30,30,QString::number(value));
        text->setParentItem(this);
        text->setPos(0,0);
        return;
    }

    double r = 13;
    double angle = 0;
    double angle_step = 2*PI/value;
    double x,y;

    for(int i = 0; i < value; i++){
        elitem = new QGraphicsEllipseItem();
        elitem->setParentItem(this);
        x = r*cos(angle);
        y = r*sin(angle);
        elitem->setRect(x-6,y-6,12,12);
        elitem->setBrush(QColor::fromRgbF(0,0,0));
        elitem->setPen(QPen(QColor::fromRgbF(0,0,0)));
        angle += angle_step;
    }
}

void ConditionItem::updateItem()
{
    foreach (ArrowItem *arrow, arrows) {
        arrow->updatePosition();
    }
}

ConditionItem::~ConditionItem()
{

}

QVariant ConditionItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (ArrowItem *arrow, arrows) {
            arrow->updatePosition();
        }
    }

    if(change == QGraphicsItem::ItemSelectedHasChanged){
        if(DiagramScene* d_scene = dynamic_cast<DiagramScene*>(this->scene())){
            d_scene->itemChanged(this);
        }
    }

    return value;
}

