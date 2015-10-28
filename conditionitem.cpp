#include "conditionitem.h"

ConditionItem::ConditionItem(QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
    this->setRect(-20,-20,40,40);
    this->setBrush(QColor::fromRgbF(0.2,0.2,0.2));
    this->setPen(QPen(QColor::fromRgbF(0,0,0)));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

ConditionItem::~ConditionItem()
{

}

