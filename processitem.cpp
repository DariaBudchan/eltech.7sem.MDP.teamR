#include "processitem.h"
#include "diagramscene.h"

ProcessItem::ProcessItem(QGraphicsItem *parent)
    :QGraphicsRectItem (parent)
{
    this->setRect(-45,-15,90,30);
    this->setPen(QPen(QColor::fromRgbF(0,0,0)));
    this->setBrush(QColor::fromRgbF(0.9,0.9,0.9));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

ProcessItem::~ProcessItem()
{

}

void ProcessItem::increaseValue()
{
    current_value++;
}

void ProcessItem::decreaseValue()
{
    if(current_value != 0){
        current_value--;
    }
}

void ProcessItem::setValue(unsigned int value)
{
    current_value = value;
}

unsigned int ProcessItem::getValue()
{
    return current_value;
}

void ProcessItem::removeArrow(ArrowItem *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void ProcessItem::removeArrows()
{
    foreach (ArrowItem *arrow, arrows) {
        arrow->disconnect();
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void ProcessItem::addArrow(ArrowItem *arrow)
{
    arrows.append(arrow);
}

void ProcessItem::updateItem()
{
    foreach (ArrowItem *arrow, arrows) {
        arrow->updatePosition();
    }
}

QVariant ProcessItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

