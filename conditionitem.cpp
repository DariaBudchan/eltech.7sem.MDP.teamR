#include "conditionitem.h"

ConditionItem::ConditionItem(QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
    this->setRect(0,0,30,30);
    this->setBrush(QColor::fromRgbF(0.2,0.2,0.2));
    this->setPen(QPen(QColor::fromRgbF(0,0,0)));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

ConditionItem::~ConditionItem()
{

}

