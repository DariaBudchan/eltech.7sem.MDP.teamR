#include "processitem.h"

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

