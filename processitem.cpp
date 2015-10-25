#include "processitem.h"

ProcessItem::ProcessItem(QGraphicsItem *parent)
    :QGraphicsRectItem (parent)
{
    this->setRect(100,100,100,50);
    this->setPen(QPen(Qt::darkGreen));
    this->setBrush(Qt::yellow);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

ProcessItem::~ProcessItem()
{

}

