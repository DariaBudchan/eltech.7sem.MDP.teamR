#include "conditionitem.h"
#include "diagramscene.h"


ConditionItem::ConditionItem(QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
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
}

void ConditionItem::decreaseValue()
{
    if(current_value != 0){
        current_value--;
    }
}

void ConditionItem::setValue(unsigned int value)
{
    current_value = value;
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
    //must be ended
}

void ConditionItem::addArrow(ArrowItem *arrow)
{
    arrows.append(arrow);
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

